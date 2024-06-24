#pragma once
#include "pattern.h"
#include "ab_color.h"
#include <cmath>

namespace RayTracer {
namespace Material {
class StripePattern :
  public Pattern,
  public ABColor {
 public:
  StripePattern() = default;

  StripePattern(const Color& a, const Color& b):
    ABColor(a, b) {
  }
  virtual ~StripePattern() {}

  Color pattern_at(const Point& p) const override {
    int floor;
    if (p.x() < 0) {
      floor = -static_cast<int>(std::ceil(-p.x()));
    } else {
      floor = static_cast<int>(p.x());
    }

    if (floor % 2 == 0) {
      return a();
    }

    return b();
  }
};

} // end of namespace Material
} // end of namespace RayTracer
