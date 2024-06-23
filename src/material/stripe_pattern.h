#pragma once
#include "pattern.h"
#include <cmath>

namespace RayTracer {
namespace Material {
class StripePattern : public Pattern {
 public:
  StripePattern():
    _a(Color::make_white()),
    _b(Color::make_black()) {
  }

  StripePattern(const Color& a, const Color& b):
    _a(a),
    _b(b) {
  }
  virtual ~StripePattern() {}

  Color a() const { return _a; }
  StripePattern& set_a(const Color& a) {
    _a = a;
    return *this;
  }

  Color b() const { return _b; }
  StripePattern& set_b(const Color& b) {
    _b = b;
    return *this;
  }

  Color pattern_at(const Point& p) const override {
    int floor;
    if (p.x() < 0) {
      floor = -static_cast<int>(std::ceil(-p.x()));
    } else {
      floor = static_cast<int>(p.x());
    }

    if (floor % 2 == 0) {
      return _a;
    }

    return _b;
  }
 private:
  Color _a;
  Color _b;
};

} // end of namespace Material
} // end of namespace RayTracer
