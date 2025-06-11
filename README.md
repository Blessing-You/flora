# Flora
Flora is a high-level C++ library for generating Material You colors.

## Overview
Flora automatically generates Material You style color palettes from images or colors. Based on Google's Material Color Utilities, it provides an easy way to generate colors and obtain palettes.

## Features
- Automatically extract color palettes from images
- Generate color schemes compliant with Material You (Material 3)
- Supports light/dark themes and contrast adjustment
- Easy to use in C++ projects

## Dependencies: 
`material-color-utilities-cpp` and `stb_image`

## Usage

```cpp
#include <Flora.hpp>
#include <iostream>

int main() {

    std::filesystem::path imagePath = "path/to/your/image.png"; // Replace with your image path
    bool isDark = false; // Set to true for dark mode
    float contrast = 0.0F; // Adjust contrast level as needed
    int bitmapSize = 1024 * 2; // Size of the bitmap to process. default is 1024x1024

    std::vector<flora::ColorPalette> palettes = flora::Flora::generateColor(imagePath, isDark, contrast, bitmapSize);
    
    if (palettes.empty()) {
        std::cout << "No color palettes generated." << std::endl;
        return 1;
    }

    for (const auto& palette : palettes) {
        std::cout << "Primary Color: " << palette.primaryColor.toHex() << std::endl;
        std::cout << "Primary Container Color: " << palette.primaryContainerColor.toHex() << std::endl;
        std::cout << "Secondary Color: " << palette.secondaryColor.toHex() << std::endl;
        std::cout << "Secondary Container Color: " << palette.secondaryContainerColor.toHex() << std::endl;
        std::cout << "Tertiary Color: " << palette.tertiaryColor.toHex() << std::endl;
        std::cout << "Tertiary Container Color: " << palette.tertiaryContainerColor.toHex() << std::endl;
        std::cout << "Background Color: " << palette.backgroundColor.toHex() << std::endl;
        std::cout << "Surface Color: " << palette.surfaceColor.toHex() << std::endl;
    }

    return 0;
}
```
