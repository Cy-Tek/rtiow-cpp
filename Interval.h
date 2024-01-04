//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef INTERVAL_H
#define INTERVAL_H

#include "Common.h"

struct Interval {
    double min, max;

    Interval() : min{infinity}, max{-infinity} {}

    Interval(const double _min, const double _max) : min{_min}, max{_max} {}

    [[nodiscard]] auto contains(const double val) const -> bool { return min <= val && val <= max; }
    [[nodiscard]] auto surrounds(const double val) const -> bool { return min < val && val < max; }

    [[nodiscard]] auto clamp(const double x) const -> double {
        if (x < min)
            return min;
        if (x > max)
            return max;
        return x;
    }

    static const Interval empty, universe;
};

static const Interval empty{infinity, -infinity};
static const Interval universe{-infinity, infinity};

#endif // INTERVAL_H
