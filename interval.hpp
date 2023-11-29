#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "utility.hpp"

class interval{
  public:
    double min, max;
    interval(double _min, double _max){ min = _min; max = _max; }

    bool contains(double x) const {
        return min < x && x< max;
    }

    double clamp(double x) const{
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
};

#endif