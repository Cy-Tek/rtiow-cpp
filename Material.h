//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Image.h"

#include "Common.h"

#include <variant>

struct ScatterResult {
    Color attenuation;
    Ray   scatter_ray;
    bool  is_visible{};
};

struct HitRecord;

class Lambertian {
public:
    Lambertian() = delete;

    explicit Lambertian(const Color &albedo) : _albedo{albedo} {}

    [[nodiscard]] auto scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult;

private:
    Color _albedo;
};

class Metal {
public:
    Metal() = delete;

    explicit Metal(const Color &albedo, const double fuzz) : _albedo{albedo}, _fuzz{fuzz} {}

    [[nodiscard]] auto scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult;

private:
    Color  _albedo;
    double _fuzz;
};

class Material {
public:
    Material() = delete;

    explicit Material(const Lambertian &lambertian) : _data{lambertian} {}
    explicit Material(const Metal &metal) : _data{metal} {}

    [[nodiscard]] auto scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult;

private:
    std::variant<Lambertian, Metal> _data;
};

#endif // MATERIAL_H
