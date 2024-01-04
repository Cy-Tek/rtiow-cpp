//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Common.h"
#include "Hittable.h"
#include "Image.h"

#include <tuple>

struct HitRecord;

using ScatterResult = std::tuple<Ray, Color, bool>;

class Material {
public:
    virtual ~Material() = default;

    virtual auto scatter(const Ray &ray, const HitRecord &record) -> ScatterResult = 0;
};

class Lambertian final : public Material {
public:
    Lambertian() = delete;

    explicit Lambertian(const Color &albedo) : _albedo{albedo} {}

    auto scatter(const Ray &ray, const HitRecord &record) -> ScatterResult override {
        auto scatter_direction = record.normal + Vec3::randomUnit();

        if (scatter_direction.nearZero())
            scatter_direction = record.normal;

        const auto scattered   = Ray{record.point, scatter_direction};
        const auto attenuation = _albedo;

        return {scattered, attenuation, true};
    }

private:
    Color _albedo;
};

class Metal final : public Material {
public:
    Metal() = delete;

    explicit Metal(const Color &albedo, const double fuzz) : _albedo{albedo}, _fuzz{fuzz} {}

    auto scatter(const Ray &ray, const HitRecord &record) -> ScatterResult override {
        const auto reflected   = ray.direction().unit().reflect(record.normal);
        const auto scattered   = Ray{record.point, reflected + _fuzz * Vec3::randomUnit()};
        const auto attenuation = _albedo;
        const auto is_visible  = scattered.direction().dot(record.normal) > 0;

        return {scattered, attenuation, is_visible};
    }

private:
    Color  _albedo;
    double _fuzz;
};

#endif // MATERIAL_H
