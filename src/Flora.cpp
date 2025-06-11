#include "Flora.hpp"
#include "Color.hpp"
#include "ColorPalette.hpp"
#include "SchemeType.hpp"
#include "cam/hct.h"
#include <vector>
#include "dynamiccolor/dynamic_scheme.h"
#include "quantize/celebi.h"
#include "quantize/wsmeans.h"
#include "scheme/scheme_content.h"
#include "scheme/scheme_expressive.h"
#include "scheme/scheme_fidelity.h"
#include "scheme/scheme_fruit_salad.h"
#include "scheme/scheme_monochrome.h"
#include "scheme/scheme_neutral.h"
#include "scheme/scheme_rainbow.h"
#include "scheme/scheme_tonal_spot.h"
#include "scheme/scheme_vibrant.h"
#include "score/score.h"
#include "stb_image.h"
#include "stb_image_resize2.h"
#include "utils/utils.h"
#include <cmath>

namespace flora {

flora::Color Flora::argbToColor(material_color_utilities::Argb argb) {
    int red = (argb & 0x00ff0000) >> 16;
    int green = (argb & 0x0000ff00) >> 8;
    int blue = (argb & 0x000000ff);
    return flora::Color(red, green, blue, 255);
}

std::vector<material_color_utilities::Hct> Flora::getImageHct(const std::filesystem::path& imagePath, int bitmapSize) {

    if (!std::filesystem::exists(imagePath)) {
        return {material_color_utilities::Hct(0, 0, 0)};
    }

    int width, height, channels;
    unsigned char* data = stbi_load(imagePath.string().c_str(), &width, &height, &channels, 4);

    if (!data) {
        return {material_color_utilities::Hct(0, 0, 0)};
    }

    int image_area = width * height;
    int bitmap_area = bitmapSize * bitmapSize;
    double scale = (image_area > bitmap_area) ? std::sqrt((double)bitmap_area / image_area) : 1.0;
    int new_width = static_cast<int>(std::round(width * scale));
    int new_height = static_cast<int>(std::round(height * scale));
    if (new_width == 0) new_width = 1;
    if (new_height == 0) new_height = 1;

    unsigned char* resized_data = data;
    bool resized = false;
    if (new_width < width || new_height < height) {
        resized_data = (unsigned char*)malloc(new_width * new_height * 4);
        if (resized_data) {
            stbir_resize_uint8_srgb(
                data, width, height, width * 4,
                resized_data, new_width, new_height, new_width * 4,
                STBIR_RGBA
            );
            resized = true;
        } else {
            resized_data = data;
            new_width = width;
            new_height = height;
        }
    }

    std::vector<material_color_utilities::Argb> pixels;
    for(int y = 0; y < new_height; y++) {
        for(int x = 0; x < new_width; x++) {
            int index = (y * new_width + x) * 4;
            unsigned char r = resized_data[index];
            unsigned char g = resized_data[index + 1];
            unsigned char b = resized_data[index + 2];
            unsigned char a = resized_data[index + 3];
            material_color_utilities::Argb argb = (a << 24) | (r << 16) | (g << 8) | b;
            pixels.push_back(argb);
        }
    }

    if (resized) {
        free(resized_data);
    }
    stbi_image_free(data);

    if(pixels.empty()) {
        return {material_color_utilities::Hct(0, 0, 0)};
    }

    material_color_utilities::QuantizerResult quantizerResult = material_color_utilities::QuantizeCelebi(pixels, 128);
    std::vector<material_color_utilities::Argb> colors = material_color_utilities::RankedSuggestions(quantizerResult.color_to_count);

    if (colors.empty()) {
        return {material_color_utilities::Hct(0, 0, 0)};
    }

    std::vector<material_color_utilities::Hct> hctColors;
    for (const auto& color : colors) {
        hctColors.push_back(material_color_utilities::Hct(color));
    }
    return hctColors;
}

material_color_utilities::DynamicScheme Flora::getDynamicSchemeByType(
    const material_color_utilities::Hct& hct,
    bool isDark,
    float contrast,
    flora::SchemeType type) {

    switch(type) {
        case flora::SchemeType::Content:
            return material_color_utilities::SchemeContent(hct, isDark, contrast);
        case flora::SchemeType::Expressive:
            return material_color_utilities::SchemeExpressive(hct, isDark, contrast);
        case flora::SchemeType::Fidelity:
            return material_color_utilities::SchemeFidelity(hct, isDark, contrast);
        case flora::SchemeType::FruitSalad:
            return material_color_utilities::SchemeFruitSalad(hct, isDark, contrast);
        case flora::SchemeType::Monochrome:
            return material_color_utilities::SchemeMonochrome(hct, isDark, contrast);
        case flora::SchemeType::Neutral:
            return material_color_utilities::SchemeNeutral(hct, isDark, contrast);
        case flora::SchemeType::Rainbow:
            return material_color_utilities::SchemeRainbow(hct, isDark, contrast);
        case flora::SchemeType::TonalSpot:
            return material_color_utilities::SchemeTonalSpot(hct, isDark, contrast);
        case flora::SchemeType::Vibrant:
            return material_color_utilities::SchemeVibrant(hct, isDark, contrast);
        default:
            return material_color_utilities::SchemeTonalSpot(hct, isDark, contrast);
    }
}

std::vector<flora::ColorPalette> Flora::generateColor(const std::filesystem::path& imagePath, 
    bool isDark, float contrast, int bitmapSize, 
    flora::SchemeType type) {

    std::vector<material_color_utilities::Hct> hctColors = getImageHct(imagePath, bitmapSize);
    std::vector<flora::ColorPalette> palettes;
    std::vector<material_color_utilities::DynamicScheme> schemes;

    for (const auto& hct : hctColors) {
        material_color_utilities::DynamicScheme scheme = getDynamicSchemeByType(hct, isDark, contrast, type);
        schemes.push_back(scheme);
    }

    for (const auto& scheme : schemes) {
        flora::ColorPalette palette;
        palette.sourceColor = argbToColor(scheme.SourceColorArgb());
        palette.primaryPaletteKeyColor = argbToColor(scheme.GetPrimaryPaletteKeyColor());
        palette.secondaryPaletteKeyColor = argbToColor(scheme.GetSecondaryPaletteKeyColor());
        palette.tertiaryPaletteKeyColor = argbToColor(scheme.GetTertiaryPaletteKeyColor());
        palette.neutralPaletteKeyColor = argbToColor(scheme.GetNeutralPaletteKeyColor());
        palette.neutralVariantPaletteKeyColor = argbToColor(scheme.GetNeutralVariantPaletteKeyColor());
        palette.backgroundColor = argbToColor(scheme.GetBackground());
        palette.onBackgroundColor = argbToColor(scheme.GetOnBackground());
        palette.surfaceColor = argbToColor(scheme.GetSurface());
        palette.surfaceDimColor = argbToColor(scheme.GetSurfaceDim());
        palette.surfaceBrightColor = argbToColor(scheme.GetSurfaceBright());
        palette.surfaceContainerLowerColor = argbToColor(scheme.GetSurfaceContainerLowest());
        palette.surfaceContainerLowColor = argbToColor(scheme.GetSurfaceContainerLow());
        palette.surfaceContainerColor = argbToColor(scheme.GetSurfaceContainer());
        palette.surfaceContainerHighColor = argbToColor(scheme.GetSurfaceContainerHigh());
        palette.surfaceContainerHighestColor = argbToColor(scheme.GetSurfaceContainerHighest());
        palette.onSurfaceColor = argbToColor(scheme.GetOnSurface());
        palette.surfaceVariantColor = argbToColor(scheme.GetSurfaceVariant());
        palette.onSurfaceVariantColor = argbToColor(scheme.GetOnSurfaceVariant());
        palette.inverseSurfaceColor = argbToColor(scheme.GetInverseSurface());
        palette.inverseOnSurfaceColor = argbToColor(scheme.GetInverseOnSurface());
        palette.outlineColor = argbToColor(scheme.GetOutline());
        palette.outlineVariantColor = argbToColor(scheme.GetOutlineVariant());
        palette.shadowColor = argbToColor(scheme.GetShadow());
        palette.scrimColor = argbToColor(scheme.GetScrim());
        palette.surfaceTintColor = argbToColor(scheme.GetSurfaceTint());
        palette.primaryColor = argbToColor(scheme.GetPrimary());
        palette.onPrimaryColor = argbToColor(scheme.GetOnPrimary());
        palette.primaryContainerColor = argbToColor(scheme.GetPrimaryContainer());
        palette.onPrimaryContainerColor = argbToColor(scheme.GetOnPrimaryContainer());
        palette.inversePrimaryColor = argbToColor(scheme.GetInversePrimary());
        palette.secondaryColor = argbToColor(scheme.GetSecondary());
        palette.onSecondaryColor = argbToColor(scheme.GetOnSecondary());
        palette.secondaryContainerColor = argbToColor(scheme.GetSecondaryContainer());
        palette.onSecondaryContainerColor = argbToColor(scheme.GetOnSecondaryContainer());
        palette.tertiaryColor = argbToColor(scheme.GetTertiary());
        palette.onTertiaryColor = argbToColor(scheme.GetOnTertiary());
        palette.tertiaryContainerColor = argbToColor(scheme.GetTertiaryContainer());
        palette.onTertiaryContainerColor = argbToColor(scheme.GetOnTertiaryContainer());
        palette.errorColor = argbToColor(scheme.GetError());
        palette.onErrorColor = argbToColor(scheme.GetOnError());
        palette.errorContainerColor = argbToColor(scheme.GetErrorContainer());
        palette.onErrorContainerColor = argbToColor(scheme.GetOnErrorContainer());
        palettes.push_back(palette);
    }

    return palettes;
}

}