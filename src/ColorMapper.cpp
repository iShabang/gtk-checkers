#include "ColorMapper.h"

#include <sstream>


ColorMapper::ColorMapper() {}

Gdk::RGBA ColorMapper::getColor(int color) {
    auto itr = m_colors.find(color);
    if (itr == m_colors.end()) {
        std::stringstream ss;
        ss << "Color: " << color << " is not registered\n";
        throw ss.str();
    }
    return itr->second;
}

void ColorMapper::registerColor(int color, Gdk::RGBA value) {
    m_colors[color] = value;
}

