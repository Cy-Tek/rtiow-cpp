//
// Created by Josh Hannaford on 1/4/24.
//

#include "Material.h"
#include "Hittable.h"

auto Lambertian::scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult {
    auto scatter_direction = record.normal + Vec3::randomUnit();

    if (scatter_direction.nearZero())
        scatter_direction = record.normal;

    const auto scattered   = Ray{record.point, scatter_direction};
    const auto attenuation = _albedo;

    return {attenuation, scattered, true};
}

auto Metal::scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult {
    const auto reflected   = ray.direction().unit().reflect(record.normal);
    const auto scattered   = Ray{record.point, reflected + _fuzz * Vec3::randomUnit()};
    const auto attenuation = _albedo;
    const auto is_visible  = scattered.direction().dot(record.normal) > 0;

    return {attenuation, scattered, is_visible};
}

auto Material::scatter(const Ray &ray, const HitRecord &record) const -> ScatterResult {
    if (std::holds_alternative<Lambertian>(_data))
        return std::get<Lambertian>(_data).scatter(ray, record);

    return std::get<Metal>(_data).scatter(ray, record);
}
