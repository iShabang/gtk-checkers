#ifndef _CHECKERS_COLOR_MAPPER_H_
#define _CHECKERS_COLOR_MAPPER_H_

#include <gdkmm/rgba.h>

#include <unordered_map>

class ColorMapper {
public:
    ColorMapper();

    ~ColorMapper() = default;
    ColorMapper(const ColorMapper &) = delete;
    ColorMapper(ColorMapper &&) = delete;
    ColorMapper &operator=(const ColorMapper &) = delete;
    ColorMapper &operator=(ColorMapper &&) = delete;

    Gdk::RGBA getColor(int color);
    void registerColor(int color, Gdk::RGBA value);

private:
    std::unordered_map<int,Gdk::RGBA> m_colors;

};

#endif //_CHECKERS_COLOR_MAPPER_H
