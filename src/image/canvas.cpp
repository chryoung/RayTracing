#include "canvas.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "utility/log_helper.h"

namespace RayTracer {
Canvas::Canvas(int width, int height) : _canvas{new Color[width * height]}, _width{width}, _height{height} {}

Canvas::~Canvas() {
  if (_canvas != nullptr) {
    delete [] _canvas;
    _canvas = nullptr;
  }
}

Canvas::Canvas(Canvas&& other) {
  _width = other._width;
  _height = other._height;
  _canvas = other._canvas;

  other._width = 0;
  other._height = 0;
  other._canvas = nullptr;
}

Canvas& Canvas::operator=(Canvas&& other) {
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
  char color_buffer[PPM_LINE_LIMIT];
  constexpr int PIXELS_PER_LINE = 5;
  constexpr int NUM_CHARS_PER_COLOR = 12;
  constexpr int RETURN_POS = PIXELS_PER_LINE * NUM_CHARS_PER_COLOR + PIXELS_PER_LINE;
  constexpr int END_POS = RETURN_POS + 1;
  const int num_pixels_cache = num_pixels();
  const int upper_limit = (num_pixels_cache / NUM_CHARS_PER_COLOR + 1) * NUM_CHARS_PER_COLOR;
  for (int i = 0; i < upper_limit; i += PIXELS_PER_LINE) {
    int num_wrote = 0;
    for (int k = i; k < i + PIXELS_PER_LINE && k < num_pixels_cache; ++k) {
      const Color& c = pixel_at(k);
      snprintf(color_buffer + num_wrote, PPM_LINE_LIMIT - num_wrote,
        "%3d %3d %3d ",
        scale_color(c.red()),
        scale_color(c.green()),
        scale_color(c.blue())
      );

      num_wrote += NUM_CHARS_PER_COLOR;
    }

    color_buffer[num_wrote - 1] = '\n';
    color_buffer[num_wrote] = '\0';
    out << color_buffer;
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
