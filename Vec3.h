//
// Created by Josh Hannaford on 11/30/23.
//

#ifndef VEC3_H
#define VEC3_H

#include "Common.h"

struct Vec3 {
    double x{0};
    double y{0};
    double z{0};

    auto operator+=(const Vec3 &v) -> void {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    auto operator*=(const double t) -> void {
        x *= t;
        y *= t;
        z *= t;
    }

    auto operator/=(const double t) -> void { *this *= 1 / t; }

    [[nodiscard]] auto operator*(const double t) const -> Vec3 {
        return {
                .x = x * t,
                .y = y * t,
                .z = z * t,
        };
    }

    [[nodiscard]] auto operator*(const Vec3 &other) const -> Vec3 {
        return {
                .x = x * other.x,
                .y = y * other.y,
                .z = z * other.z,
        };
    }

    [[nodiscard]] auto operator-() const -> Vec3 { return Vec3{-x, -y, -z}; }
    [[nodiscard]] auto operator/(const double t) const -> Vec3 { return *this * (1 / t); }

    [[nodiscard]] auto operator-(const Vec3 &v) const -> Vec3 {
        return {
                .x = x - v.x,
                .y = y - v.y,
                .z = z - v.z,
        };
    }

    [[nodiscard]] auto operator+(const Vec3 &v) const -> Vec3 {
        return {
                .x = x + v.x,
                .y = y + v.y,
                .z = z + v.z,
        };
    }

    [[nodiscard]] auto dot(const Vec3 &v) const -> double { return x * v.x + y * v.y + z * v.z; }
    [[nodiscard]] auto lengthSquared() const -> double { return dot(*this); }
    [[nodiscard]] auto length() const -> double { return sqrt(lengthSquared()); }
    [[nodiscard]] auto unit() const -> Vec3 { return *this / length(); }
    [[nodiscard]] auto reflect(const Vec3 &normal) const -> Vec3 { return *this - normal * this->dot(normal) * 2; }

    [[nodiscard]] auto nearZero() const -> bool {
        constexpr auto s = 1e-8;
        return fabs(x) < s && fabs(y) < s && fabs(z) < s;
    }

    // Static member functions

    auto static random() -> Vec3 {
        return {
                .x = randomDouble(),
                .y = randomDouble(),
                .z = randomDouble(),
        };
    }

    auto static random(const double min, const double max) -> Vec3 {
        return {
                .x = randomDouble(min, max),
                .y = randomDouble(min, max),
                .z = randomDouble(min, max),
        };
    }

    auto static randomInUnitSphere() -> Vec3 {
        auto p = random(-1, 1);
        while (p.lengthSquared() >= 1) {
            p = random(-1, 1);
        }

        return p;
    }

    auto static randomUnit() -> Vec3 { return randomInUnitSphere().unit(); }

    auto static randomOnHempisphere(const Vec3 &normal) -> Vec3 {
        const auto onUnitSphere = randomUnit();

        if (onUnitSphere.dot(normal) > 0.0) // In the same hemisphere as the normal
            return onUnitSphere;

        return -onUnitSphere;
    }
};

auto inline operator*(const double t, const Vec3 &vec) -> Vec3 {
    return {
            .x = t * vec.x,
            .y = t * vec.y,
            .z = t * vec.z,
    };
}


using Point3 = Vec3;

#endif // VEC3_H
