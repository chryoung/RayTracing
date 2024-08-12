#include "canvas.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <ranges>
#include <format>

#include "utility/log_helper.h"

namespace RayTracer {
Canvas::Canvas(int width, int height) : _canvas{new Color[width * height]}, _width{width}, _height{height} {}

Canvas::~Canvas() {
  if (_canvas != nullptr) {
    delete [] _canvas;
    _canvas = nullptr;
  }
}

Canvas::Canvas(Canvas&& other) noexcept {
  _width = other._width;
  _height = other._height;
  _canvas = other._canvas;

  other._width = 0;
  other._height = 0;
  other._canvas = nullptr;
}

Canvas& Canvas::operator=(Canvas&& other) noexcept {
  if (this != &other) {
    if (_canvas != nullptr) {
      delete [] _canvas;
      _canvas = nullptr;
    }

    _width = other._width;
    _height = other._height;
    _canvas = other._canvas;

    other._width = 0;
    other._height = 0;
    other._canvas = nullptr;
  }

  return *this;
}

Canvas Canvas::create(int width, int height) {
  if (width <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " create: Canvas width should not be less or equal than 0.");
  }

  if (height <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " create: Canvas height should not be less or equal than 0.");
  }

  return Canvas(width, height);
}

Canvas& Canvas::write_pixel(int x, int y, const Color& color) {
  if (x < 0 || x >= width() || y < 0 || y >= height()) {
    throw std::out_of_range(CURRENT_LINE + " write_pixel: x or y is out of range.");
  }

  _canvas[x * _height + y] = color;

  return *this;
}

const Color& Canvas::pixel_at(int x, int y) const {
  if (x < 0 || x >= width() || y < 0 || y >= height()) {
    throw std::out_of_range(CURRENT_LINE + " pixel_at: x or y is out of range.");
  }

  return _canvas[x * _height + y];
}

const Color& Canvas::pixel_at(int index) const {
  if (index < 0 || index >= num_pixels()) {
    throw std::out_of_range(CURRENT_LINE + " pixel_at: x or y is out of range.");
  }

  int x = index % _width;
  int y = index / _width;
  return _canvas[x * _height + y];
}

size_t Canvas::width() const { return _width; }

size_t Canvas::height() const { return _height; }

size_t Canvas::num_pixels() const { return height() * width(); }

bool Canvas::to_ppm(std::ostream& out) const {
    using namespace std;

    const char* ppm_magic_number = "P3";

    // Write PPM header.
    out << ppm_magic_number << "\n" << width() << " " << height() << "\n" << COLOR_LIMIT << "\n";

    // Write pixels.
    constexpr int PIXELS_PER_LINE = 5;
    const auto num_pixels_cache = static_cast<int>(num_pixels());

    auto pixels = ranges::views::iota(0, num_pixels_cache)
                | ranges::views::transform([this](int k) {
                    const Color& c = pixel_at(k);
                    return format("{:3d} {:3d} {:3d}", scale_color(c.red()), scale_color(c.green()), scale_color(c.blue()));
                  });

    int count = 0;
    for (const auto& pixel : pixels) {
        out << pixel << " ";
        ++count;
        if (count % PIXELS_PER_LINE == 0) {
            out.seekp(-1, ios_base::cur); // Move back one character to overwrite the last space
            out << "\n";
        }
    }

    if (count % PIXELS_PER_LINE != 0) {
        out.seekp(-1, ios_base::end); // Move back one character to overwrite the last space
    }

    return true;
}

bool Canvas::to_file(const std::string& file_name) const {
  std::ofstream output(file_name);
  bool result = to_ppm(output);
  output.close();
  return result;
}

int Canvas::scale_color(double color_component) {
  int scaled = static_cast<int>((color_component * COLOR_LIMIT) + 0.5);  // Upper cap
  if (scaled < 0) {
    return 0;
  } else if (scaled > COLOR_LIMIT) {
    return COLOR_LIMIT;
  } else {
    return scaled;
  }
}
}  // namespace RayTracer
