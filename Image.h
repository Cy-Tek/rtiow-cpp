//
// Created by Josh Hannaford on 1/2/24.
//

#ifndef IMAGE_H
#define IMAGE_H

#include "Common.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

using std::vector;

// Colors

using Color = Vec3;

namespace color {
    static constexpr auto Black = Color{0, 0, 0};
    static constexpr auto White = Color{1, 1, 1};
    static constexpr auto Red   = Color{1, 0, 0};
    static constexpr auto Green = Color{0, 1, 0};
    static constexpr auto Blue  = Color{0, 0, 1};
} // namespace color

auto inline operator<<(std::ostream &out, Color color) -> std::ostream & {
    const auto [r, g, b] = color;

    // Clamp the color values to ensure they stay in the 0..=255 range
    static const Interval intensity{0.000, 0.999};
    return out << static_cast<int>(255.999 * intensity.clamp(r)) << ' '
               << static_cast<int>(255.999 * intensity.clamp(g)) << ' '
               << static_cast<int>(255.999 * intensity.clamp(b));
}

// Image

class Image {
public:
    int _width, _height;

    Image() = delete;
    Image(const int width, const int height) : _width{width}, _height{height} { _data.resize(_width * _height); }

    auto setPixel(const int x, const int y, const Color &color) -> void { _data[coordsToIndex(x, y)] = color; }

    [[nodiscard]] auto getPixel(const int x, const int y) -> Color & { return _data[coordsToIndex(x, y)]; }

    [[nodiscard]] auto writeToFile(const fs::path &path) const -> bool {
        std::ofstream file{path};
        if (!file)
            return false;

        file << "P3\n" << _width << ' ' << _height << "\n255\n";
        for (const auto &pixel: _data) {
            file << pixel << '\n';
        }

        return true;
    }

private:
    vector<Color> _data;

    [[nodiscard]] auto coordsToIndex(const int x, const int y) const -> int { return y * _width + x; }
};

#endif // IMAGE_H
