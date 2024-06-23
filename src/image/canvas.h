#pragma once
#include <ostream>
#include <string>
#include <vector>

#include "color.h"

namespace RayTracer {
class Canvas {
 public:
  static Canvas create(int width, int height);
  Canvas(const Canvas&) = delete;
  Canvas(Canvas&& other);
  Canvas& operator=(const Canvas&) = delete;
  Canvas& operator=(Canvas&& other);
  virtual ~Canvas();
  Canvas& write_pixel(int x, int y, const Color& color);
  const Color& pixel_at(int x, int y) const;
  const Color& pixel_at(int index) const;
  size_t width() const;
  size_t height() const;
  size_t num_pixels() const;

  /**
   * @brief Saves the Canvas to PPM file.
   * @param out The stream to be written.
   * @returns True if saved. Otherwise false.
   */
  bool to_ppm(std::ostream& out) const;

  bool to_file(const std::string& file_name) const;

 private:
  Canvas(int width, int height);

  /**
   * @brief Scales the double to the int color component by COLOR_LIMIT.
   * @param color_component The color component to be scaled.
   * @returns Scaled color which is rounded up and limitted between 0 and COLOR_LIMIT.
   */
  static int scale_color(double color_component);

  static constexpr int PPM_LINE_LIMIT = 70;
  static constexpr int COLOR_LIMIT = 255;

  Color* _canvas;
  int _width;
  int _height;
};
}  // namespace RayTracer

