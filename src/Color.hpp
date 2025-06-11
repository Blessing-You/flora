#pragma once

#include <iomanip>
#include <sstream>
#include <string>

namespace flora {

class Color {
    public:
        int red;
        int green;
        int blue;
        int alpha = 255;
        
        Color() : red(0), green(0), blue(0), alpha(255) {}
        Color(int r, int g, int b, int a = 255) : red(r), green(g), blue(b), alpha(a) {}

        std::string toHex() const {
            std::stringstream ss;
            ss << "#" << std::hex << std::setfill('0') 
            << std::setw(2) << red 
            << std::setw(2) << green 
            << std::setw(2) << blue;
            return ss.str();
        };
};

} // namespace flora