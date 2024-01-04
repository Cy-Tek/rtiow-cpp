//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef COMMON_H
#define COMMON_H


#include <cmath>
#include <limits>
#include <memory>
#include <optional>
#include <random>

// Usings

using std::make_shared;
using std::optional;
using std::shared_ptr;
using std::sqrt;

// Constants

const double     infinity = std::numeric_limits<double>::infinity();
constexpr double pi       = 3.1415926535897932385;

// Utility functions

auto inline degreesToRadians(const double degrees) -> double { return degrees * pi / 180; }

auto inline randomDouble() -> double {
    static std::uniform_real_distribution<double> distribution(0, 1);
    static std::mt19937                           generator;
    return distribution(generator);
}

auto inline randomDouble(const double min, const double max) -> double { return min + (max - min) * randomDouble(); }

// Common Headers

#include "Interval.h"
#include "Ray.h"
#include "Vec3.h"

#endif // COMMON_H
