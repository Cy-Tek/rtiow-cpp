#include "Camera.h"
#include "HittableList.h"
#include "Sphere.h"

auto main() -> int {
    auto material_ground = Material{Lambertian{Color{0.8, 0.8, 0.0}}};
    auto material_center = Material{Lambertian{Color{0.7, 0.3, 0.3}}};
    auto material_left   = Material{Metal{Color{0.8, 0.8, 0.8}, 0.3}};
    auto material_right  = Material{Metal{Color{0.8, 0.6, 0.2}, 1.0}};

    HittableList world{};
    world.add(Sphere{Point3{0, -100.5, -1}, 100, material_ground});
    world.add(Sphere{Point3{0, 0, -1}, 0.5, material_center});
    world.add(Sphere{Point3{-1, 0, -1}, 0.5, material_left});
    world.add(Sphere{Point3{1, 0, -1}, 0.5, material_right});

    auto camera = Camera().aspectRatio(16.0 / 9.0).imageWidth(400).samplesPerPixel(100).maxDepth(50);
    camera.render(world);

    return 0;
}
