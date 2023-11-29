#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

/* Record color in RGB value */
using rgb = vec3;

void write_rgb(std::ostream &out, rgb color){
    out << static_cast<int>(255 * color.x()) << ' '
        << static_cast<int>(255 * color.y()) << ' '
        << static_cast<int>(255 * color.z()) << ' ';
}

#endif