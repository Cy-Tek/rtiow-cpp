//
// Created by Josh Hannaford on 1/2/24.
//

#ifndef SPHERE_H
#define SPHERE_H

#include <utility>

#include "Hittable.h"
#include "Vec3.h"

class Sphere final : public Hittable {
public:
    Sphere() = delete;
    Sphere(const Point3 &center, const double radius, shared_ptr<Material> material) :
        _center{center}, _radius{radius}, _material{std::move(material)} {}

    [[nodiscard]] auto hit(const Ray &ray, const Interval rayT) const -> optional<HitRecord> override {
        const Vec3   oc    = ray.origin() - _center;
        const double a     = ray.direction().lengthSquared();
        const double halfB = oc.dot(ray.direction());
        const double c     = oc.lengthSquared() - _radius * _radius;

        const double discriminant = halfB * halfB - a * c;
        if (discriminant < 0)
            return std::nullopt;

        const double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        double root = (-halfB - sqrtd) / a;
        if (!rayT.surrounds(root)) {
            root = (-halfB + sqrtd) / a;
            if (!rayT.surrounds(root)) {
                return std::nullopt;
            }
        }

        auto record     = HitRecord{};
        record.distance = root;
        record.point    = ray.at(record.distance);
        record.material = _material;

        const Vec3 outwardNormal = (record.point - _center) / _radius;
        record.setFaceNormal(ray, outwardNormal);

        return std::optional{record};
    }

private:
    Point3               _center;
    double               _radius;
    shared_ptr<Material> _material;
};

#endif // SPHERE_H
