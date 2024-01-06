//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"

#include <vector>
#include "Sphere.h"

using std::vector;

class HittableList {
public:
    HittableList() = default;

    explicit HittableList(const Sphere &object) { add(object); }

    auto add(const Sphere &object) -> void { _spheres.push_back(object); }
    auto clear() -> void { _spheres.clear(); }

    [[nodiscard]] auto hit(const Ray &ray, const Interval rayT) const -> optional<HitRecord> {
        optional<HitRecord> result = std::nullopt;

        double closestSoFar = rayT.max;
        for (const auto &sphere: _spheres) {
            if (auto hitRecord = sphere.hit(ray, {rayT.min, closestSoFar}); hitRecord.has_value()) {
                closestSoFar = hitRecord->distance;
                result       = hitRecord;
            }
        }

        return result;
    }

private:
    vector<Sphere> _spheres;
};

#endif // HITTABLELIST_H
