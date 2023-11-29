#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include "utility.hpp"

class interval{
  public:
    double min, max;
    interval(double _min, double _max){ min = _min; _max = max; }

    bool contains(double x) const {
        return min <= x && x<= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }
};

static const interval empty = interval(+infinity, -infinity);
static const interval universe = interval(-infinity, +infinity);

#endif