#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double deg_to_rad(double deg){
    return deg * pi / 180.0;
}

#endif