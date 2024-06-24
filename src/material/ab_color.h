#pragma once
#include "image/color.h"

namespace RayTracer {
namespace Material {
class ABColor {
public:
  ABColor():
    _a(Color::make_white()),
    _b(Color::make_black())
  {}

  ABColor(const Color& a, const Color& b):
    _a(a),
    _b(b)
  {}

  virtual Color a() const { return _a; }
  virtual ABColor& set_a(const Color& a) {
    _a = a;
    return *this;
  }

  virtual Color b() const { return _b; }
  virtual ABColor& set_b(const Color& b) {
    _b = b;
    return *this;
  }
private:
  Color _a;
  Color _b;
};
}
}
