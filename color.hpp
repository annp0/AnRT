#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

/* Record color in RGB value */
using rgb = vec3;

void write_rgb(std::ostream &out, rgb color, int samples_per_pixel){
    auto scale = 1.0 / samples_per_pixel;
    auto r = color.x() * scale;
    auto g = color.y() * scale;
    auto b = color.z() * scale;
    
    static const interval range(0.000, 0.999);
    out << static_cast<int>(256 * range.clamp(r)) << ' '
        << static_cast<int>(256 * range.clamp(g)) << ' '
        << static_cast<int>(256 * range.clamp(b)) << ' ';
}

#endif