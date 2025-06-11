#pragma once

#include "Color.hpp"
#include "ColorPalette.hpp"
#include "SchemeType.hpp"
#include "cam/hct.h"
#include "dynamiccolor/dynamic_scheme.h"
#include "utils/utils.h"
#include <filesystem>
#include <vector>

namespace flora {

class Flora {
    
    private:
        static flora::Color argbToColor(material_color_utilities::Argb argb);
        static std::vector<material_color_utilities::Hct> getImageHct(const std::filesystem::path& imagePath, int bitmapSize = 1024);
        static material_color_utilities::DynamicScheme getDynamicSchemeByType(
            const material_color_utilities::Hct& hct,
            bool isDark,
            float contrast = 0.0F,
            flora::SchemeType type = flora::SchemeType::TonalSpot
        );

    public:
        static std::vector<flora::ColorPalette> generateColor(const std::filesystem::path& imagePath, 
            bool isDark, float contrast = 0.0F, int bitmapSize = 1024, 
            flora::SchemeType type = flora::SchemeType::TonalSpot);
};

}