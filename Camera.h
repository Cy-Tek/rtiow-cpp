//
// Created by Josh Hannaford on 1/3/24.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"

#include "Hittable.h"
#include "Image.h"
#include "Material.h"

auto inline linearToGamma(const double component) -> double { return sqrt(component); }

class Camera {
public:
    auto render(const Hittable &world) -> void {
        initialize();

        Image image{_image_width, _image_height};
        for (int y = 0; y < _image_height; ++y) {
            std::clog << "\rScanlines remaining: " << _image_height - y << ' ' << std::flush;

            for (int x = 0; x < _image_width; ++x) {
                Color pixel_color{0, 0, 0};
                for (int sample = 0; sample < _samples_per_pixel; ++sample) {
                    const auto ray = getRay(x, y);
                    pixel_color += rayColor(ray, _max_depth, world);
                }

                // Normalize the color value
                pixel_color /= _samples_per_pixel;

                // To gamma space
                pixel_color.x = linearToGamma(pixel_color.x);
                pixel_color.y = linearToGamma(pixel_color.y);
                pixel_color.z = linearToGamma(pixel_color.z);

                image.setPixel(x, y, pixel_color);
            }
        }

        std::clog << "\rDone creating image.                        \n"
                  << "Writing to file...\n";

        if (const auto path{"../image.ppm"}; !image.writeToFile(path)) {
            std::clog << "Failed to write to path: " << path << '\n';
            exit(1);
        }

        std::clog << "Done\n";
    }

    auto aspectRatio(const double ratio) -> Camera & {
        _aspect_ratio = ratio;
        return *this;
    }

    auto imageWidth(const int width) -> Camera & {
        _image_width = width;
        return *this;
    }

    auto samplesPerPixel(const int samples) -> Camera & {
        _samples_per_pixel = samples;
        return *this;
    }

    auto maxDepth(const int depth) -> Camera & {
        _max_depth = depth;
        return *this;
    }

private:
    // Configurable vars
    int    _image_width  = 100;
    double _aspect_ratio = 1.0;

    int _samples_per_pixel = 10;
    int _max_depth         = 10;

    // Generated vars based on the configurations
    int _image_height{};

    Point3 _center;
    Point3 _pixel00_loc;
    Vec3   _pixel_delta_u;
    Vec3   _pixel_delta_v;


    auto initialize() -> void {
        _image_height = static_cast<int>(_image_width / _aspect_ratio);
        _image_height = _image_height >= 1 ? _image_height : 1;

        _center = {0, 0, 0};

        constexpr auto focal_length    = 1.0;
        constexpr auto viewport_height = 2.0;
        const auto     viewport_width  = viewport_height * (static_cast<double>(_image_width) / _image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges
        const auto     viewport_u = Vec3{viewport_width, 0, 0};
        constexpr auto viewport_v = Vec3{0, -viewport_height, 0};

        // Calculate the horizontal and vertical delta vectors from pixel to pixel
        _pixel_delta_u = viewport_u / _image_width;
        _pixel_delta_v = viewport_v / _image_height;

        // Calculate the location of the upper left pixel
        const auto viewport_upper_left = _center - Vec3{0, 0, focal_length} - viewport_u / 2 - viewport_v / 2;

        _pixel00_loc = viewport_upper_left + 0.5 * (_pixel_delta_u + _pixel_delta_v);
    }

    [[nodiscard]] auto getRay(const int x, const int y) const -> Ray {
        const Point3 pixel_center = _pixel00_loc + (x * _pixel_delta_u) + (y * _pixel_delta_v);
        const Point3 pixel_sample = pixel_center + pixelSampleSquare();

        const Vec3 ray_center    = _center;
        const Vec3 ray_direction = pixel_sample - ray_center;

        return {ray_center, ray_direction};
    }

    [[nodiscard]] auto pixelSampleSquare() const -> Vec3 {
        const auto px = -0.5 + randomDouble();
        const auto py = -0.5 + randomDouble();
        return px * _pixel_delta_u + py * _pixel_delta_v;
    }

    [[nodiscard]] auto rayColor(const Ray &ray, const int depth, const Hittable &world) const -> Color {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (depth <= 0)
            return color::Black;

        if (const auto hit = world.hit(ray, {0.001, infinity}); hit.has_value()) {
            const auto [scattered, attenuation, reflected] = hit->material->scatter(ray, hit.value());
            if (reflected)
                return attenuation * rayColor(scattered, depth - 1, world);

            return color::Black;
        }

        const Vec3     unitDirection = ray.direction().unit();
        const double   a             = 0.5 * (unitDirection.y + 1);
        constexpr auto skyBlue       = Color{0.5, 0.7, 1.0};

        return (1.0 - a) * color::White + a * skyBlue;
    }
};

#endif // CAMERA_H
