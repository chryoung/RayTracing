#ifndef C66010A5_4D2D_48DF_B8BF_7CE9A0F66900
#define C66010A5_4D2D_48DF_B8BF_7CE9A0F66900

#include <ostream>
#include <vector>
#include <string>

#include "color.h"

namespace RayTracer {
class Canvas {
 public:
  Canvas(int width, int height);
  ~Canvas();
  Canvas& write_pixel(int x, int y, const Color& color);
  Color& pixel_at(int x, int y);
  const Color& pixel_at(int x, int y) const;
  int width();
  int width() const;
  int height();
  int height() const;

  /**
   * @brief Saves the Canvas to PPM file.
   * @param out The stream to be written.
   * @returns True if saved. Otherwise false.
   */
  bool to_ppm(std::ostream& out);

  /**
   * @brief Saves the Canvas to PPM file.
   * @param out The stream to be written.
   * @returns True if saved. Otherwise false.
   */
  bool to_ppm(std::ostream& out) const;
  
  /**
   * @brief Breaks the string into lines which won't exceed PPM_LINE_LIMIT.
   * @param line The string which will be broken.
   * @returns A vector of strings.
   */
  static std::vector<std::string> break_line(std::string line);

 private:
  /**
   * @brief Scales the double to the int color component by COLOR_LIMIT.
   * @param color_component The color component to be scaled.
   * @returns Scaled color which is rounded up and limitted between 0 and COLOR_LIMIT.
   */
  static int scale_color(double color_component);

  static constexpr int PPM_LINE_LIMIT = 70;
  static constexpr int COLOR_LIMIT = 255;

  std::vector<std::vector<Color>> _canvas;
};
}  // namespace RayTracer

#endif /* C66010A5_4D2D_48DF_B8BF_7CE9A0F66900 */
