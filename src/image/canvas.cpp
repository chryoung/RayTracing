#include "canvas.h"

#include <cstdio>
#include <exception>
#include <iostream>
#include <string>

#include "utility/log_helper.h"

namespace RayTracer {
Canvas::Canvas(int width, int height) : _canvas(std::vector<std::vector<Color>>(width, std::vector<Color>(height))) {}

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

  _canvas[x][y] = color;

  return *this;
}

Color& Canvas::pixel_at(int x, int y) {
  if (x < 0 || x >= width() || y < 0 || y >= height()) {
    throw std::out_of_range(CURRENT_LINE + " pixel_at: x or y is out of range.");
  }

  return _canvas[x][y];
}

const Color& Canvas::pixel_at(int x, int y) const {
  if (x < 0 || x >= width() || y < 0 || y >= height()) {
    throw std::out_of_range(CURRENT_LINE + " pixel_at: x or y is out of range.");
  }

  return _canvas[x][y];
}

int Canvas::width() { return _canvas.size(); }

int Canvas::width() const { return _canvas.size(); }

int Canvas::height() { return _canvas[0].size(); }

int Canvas::height() const { return _canvas[0].size(); }

bool Canvas::to_ppm(std::ostream& out) const { return const_cast<Canvas&>(*this).to_ppm(out); }

std::vector<std::string> Canvas::break_line(std::string line) {
  if (line.size() < PPM_LINE_LIMIT) {
    return std::vector<std::string>{line};
  }

  std::vector<std::string> lines;
  int start = 0;
  while (start < line.size() - PPM_LINE_LIMIT) {
    int end = start + PPM_LINE_LIMIT;
    if (line[end] == ' ') {
      lines.emplace_back(line.substr(start, end - start - 1) + "\n");
    } else {
      while (end > start && line[end] != ' ') {
        end--;
      }
      if (end <= start) {
        break;
      }
      lines.emplace_back(line.substr(start, end - start) + "\n");
    }
    start = end + 1;
  }
  int count = line.size() - start - 1;
  lines.emplace_back(line.substr(start, line.size() - start - 1) + "\n");

  return lines;
}

bool Canvas::to_ppm(std::ostream& out) {
  using namespace std;

  const char* ppm_magic_number = "P3";

  // Write PPM header.
  out << ppm_magic_number << "\n" << width() << " " << height() << "\n" << COLOR_LIMIT << "\n";

  // Write pixels.
  string buffer;
  constexpr int COLOR_BUFFER_SIZE = 13;
  char color_buffer[COLOR_BUFFER_SIZE];
  for (int y = 0; y < height(); y++) {
    for (int x = 0; x < width(); x++) {
      const auto& pixel = pixel_at(x, y);
      snprintf(color_buffer, COLOR_BUFFER_SIZE, "%d %d %d ", scale_color(pixel.red()), scale_color(pixel.green()),
               scale_color(pixel.blue()));
      buffer += color_buffer;
    }
    buffer[buffer.size() - 1] = '\n';
    auto lines = break_line(buffer);
    for (const auto& line : lines) {
      out << line;
    }
    buffer.clear();
  }

  return true;
}

int Canvas::scale_color(double color_component) {
  int scaled = (color_component * COLOR_LIMIT) + 0.5;  // Upper cap
  if (scaled < 0) {
    return 0;
  } else if (scaled > COLOR_LIMIT) {
    return COLOR_LIMIT;
  } else {
    return scaled;
  }
}
}  // namespace RayTracer