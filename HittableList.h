//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"

#include <vector>

using std::vector;

class HittableList final : public Hittable {
public:
    HittableList() = default;

    explicit HittableList(const shared_ptr<Hittable> &object) { add(object); }

    auto add(const shared_ptr<Hittable> &object) -> void { mObjects.push_back(object); }
    auto clear() -> void { mObjects.clear(); }

    [[nodiscard]] auto hit(const Ray &ray, const Interval rayT) const -> optional<HitRecord> override {
        optional<HitRecord> result       = std::nullopt;
        double              closestSoFar = rayT.max;

        for (const auto &object: mObjects) {
            if (auto hitRecord = object->hit(ray, {rayT.min, closestSoFar}); hitRecord.has_value()) {
                closestSoFar = hitRecord->distance;
                result       = hitRecord;
            }
        }

        return result;
    }

private:
    vector<shared_ptr<Hittable>> mObjects;
};

#endif // HITTABLELIST_H
