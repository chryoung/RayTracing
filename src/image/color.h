#pragma once
#include <ostream>

#include "utility/utility.h"

namespace RayTracer {
class Color {
 public:
  Color(double red, double green, double blue) : _red(red), _green(green), _blue(blue) {}
  Color(double factor): _red(factor), _green(factor), _blue(factor) {}
  Color() : Color(0, 0, 0) {}

  double red() const { return _red; }
  double green() const { return _green; }
  double blue() const { return _blue; }

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

  static Color make_black() { return Color(0); }

  static Color make_white() { return Color(1); }

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

inline Color operator*(const Color& a, double s) { return Color(a.red() * s, a.green() * s, a.blue() * s); }

inline Color operator*(double s, const Color& a) { return Color(a.red() * s, a.green() * s, a.blue() * s); }

inline Color operator*(const Color& a, const Color& b) {
  return Color(a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue());
}

inline bool operator==(const Color& a, const Color& b) {
  return is_double_eq(a.red(), b.red()) && is_double_eq(a.green(), b.green()) && is_double_eq(a.blue(), b.blue());
}

inline bool operator!=(const Color& a, const Color& b) { return !(a == b); }

inline std::ostream& operator<<(std::ostream& out, const Color& a) {
  out << "Color(" << a.red() << ", " << a.green() << ", " << a.blue() << ")";

  return out;
}
}  // namespace RayTracer

