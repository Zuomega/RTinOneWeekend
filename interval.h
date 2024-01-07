#ifndef INTERVAL_H
#define INTERVAL_H

#include "utils.h"

class interval {
  public:
    FLOAT_FORMAT min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(FLOAT_FORMAT _min, FLOAT_FORMAT _max) : min(_min), max(_max) {}

    bool contains(FLOAT_FORMAT x) const {
        return min <= x && x <= max;
    }

    bool surrounds(FLOAT_FORMAT x) const {
        return min < x && x < max;
    }

    FLOAT_FORMAT clamp(FLOAT_FORMAT x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const static interval empty   (+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif