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
