#pragma once

#include "Color.hpp"
#include "ColorPalette.hpp"
#include "cam/hct.h"
#include "utils/utils.h"
#include <filesystem>
#include <vector>

namespace flora {

class Flora {
    
    private:
        static flora::Color argbToColor(material_color_utilities::Argb argb);
        static std::vector<material_color_utilities::Hct> getImageHct(const std::filesystem::path& imagePath, int bitmapSize = 1024);

    public:
        static std::vector<flora::ColorPalette> generateColor(const std::filesystem::path& imagePath, bool isDark, float contrast = 0.0F, int bitmapSize = 1024);
};

}