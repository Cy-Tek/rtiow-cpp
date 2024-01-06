//
// Created by Josh Hannaford on 1/2/24.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include "Material.h"
#include "Ray.h"

struct HitRecord {
    Point3 point;
    Vec3   normal;

    double distance{};
    bool   frontFace{};

    Material material;

    auto setFaceNormal(const Ray &ray, const Vec3 &outwardNormal) -> void {
        frontFace = ray.direction().dot(outwardNormal) < 0;
        normal    = frontFace ? outwardNormal : -outwardNormal;
    }
};

#endif // HITTABLE_H
