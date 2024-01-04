//
// Created by Josh Hannaford on 1/2/24.
//

#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:
    Ray() = default;

    Ray(const Point3 &origin, const Vec3 &direction) : _origin{origin}, _direction{direction} {}

    [[nodiscard]] auto origin() const -> Point3 { return _origin; }
    [[nodiscard]] auto direction() const -> Vec3 { return _direction; }
    [[nodiscard]] auto at(double t) const -> Point3 { return _origin + t * _direction; }

private:
    Point3 _origin;
    Vec3   _direction;
};


#endif // RAY_H
