//
// Created by Josh Hannaford on 1/2/24.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include "Ray.h"

class Material;

struct HitRecord {
    Point3 point;
    Vec3   normal;

    double distance{};
    bool   frontFace{};

    shared_ptr<Material> material;

    auto setFaceNormal(const Ray &ray, const Vec3 &outwardNormal) -> void {
        frontFace = ray.direction().dot(outwardNormal) < 0;
        normal    = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    [[nodiscard]] auto virtual hit(const Ray &ray, Interval rayT) const -> optional<HitRecord> = 0;
};

#endif // HITTABLE_H
