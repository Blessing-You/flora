#pragma once

#include "Color.hpp"

namespace flora {

struct ColorPalette {
    flora::Color sourceColor;
    flora::Color primaryPaletteKeyColor;
    flora::Color secondaryPaletteKeyColor;
    flora::Color tertiaryPaletteKeyColor;
    flora::Color neutralPaletteKeyColor;
    flora::Color neutralVariantPaletteKeyColor;
    flora::Color backgroundColor;
    flora::Color onBackgroundColor;
    flora::Color surfaceColor;
    flora::Color surfaceDimColor;
    flora::Color surfaceBrightColor;
    flora::Color surfaceContainerLowerColor;
    flora::Color surfaceContainerLowColor;
    flora::Color surfaceContainerColor;
    flora::Color surfaceContainerHighColor;
    flora::Color surfaceContainerHighestColor;
    flora::Color onSurfaceColor;
    flora::Color surfaceVariantColor;
    flora::Color onSurfaceVariantColor;
    flora::Color inverseSurfaceColor;
    flora::Color inverseOnSurfaceColor;
    flora::Color outlineColor;
    flora::Color outlineVariantColor;
    flora::Color shadowColor;
    flora::Color scrimColor;
    flora::Color surfaceTintColor;
    flora::Color primaryColor;
    flora::Color onPrimaryColor;
    flora::Color primaryContainerColor;
    flora::Color onPrimaryContainerColor;
    flora::Color inversePrimaryColor;
    flora::Color secondaryColor;
    flora::Color onSecondaryColor;
    flora::Color secondaryContainerColor;
    flora::Color onSecondaryContainerColor;
    flora::Color tertiaryColor;
    flora::Color onTertiaryColor;
    flora::Color tertiaryContainerColor;
    flora::Color onTertiaryContainerColor;
    flora::Color errorColor;
    flora::Color onErrorColor;
    flora::Color errorContainerColor;
    flora::Color onErrorContainerColor;
};

} // namespace flora