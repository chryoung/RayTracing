#ifndef F38A44CE_973D_4B33_B053_0D5724AA80E6
#define F38A44CE_973D_4B33_B053_0D5724AA80E6

#include <ostream>

#include "utility/utility.h"

namespace RayTracer {
class Color {
 public:
  Color(double red, double green, double blue)
      : _red(red), _green(green), _blue(blue) {}
  Color() : Color(0, 0, 0) {}

  double red() const { return _red; }
  double green() const { return _green; }
  double blue() const { return _blue; }

  double red() { return _red; }
  double green() { return _green; }
  double blue() { return _blue; }

  Color& set_red(double red) {
    _red = red;
    return *this;
  }

  Color& set_green(double green) {
    _green = green;
    return *this;
  }
  Color& set_blue(double blue) {
    _blue = blue;
    return *this;
  }

 private:
  double _red;
  double _green;
  double _blue;
};

inline Color operator+(const Color& a, const Color& b) {
  return Color(a.red() + b.red(), a.green() + b.green(), a.blue() + b.blue());
}

inline Color operator-(const Color& a, const Color& b) {
  return Color(a.red() - b.red(), a.green() - b.green(), a.blue() - b.blue());
}

inline Color operator*(const Color& a, double s) {
  return Color(a.red() * s, a.green() * s, a.blue() * s);
}

inline Color operator*(double s, const Color& a) {
  return Color(a.red() * s, a.green() * s, a.blue() * s);
}

inline Color operator*(const Color& a, const Color& b) {
  return Color(a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue());
}

inline bool operator==(const Color& a, const Color& b) {
  return is_double_eq(a.red(), b.red()) &&
         is_double_eq(a.green(), b.green()) &&
         is_double_eq(a.blue(), b.blue());
}

inline bool operator!=(const Color& a, const Color& b) { return !(a == b); }

inline std::ostream& operator<<(std::ostream& out, const Color& a) {
  out << "(" << a.red() << ", " << a.green() << ", " << a.blue() << ")";

  return out;
}
}  // namespace RayTracer

#endif /* F38A44CE_973D_4B33_B053_0D5724AA80E6 */
