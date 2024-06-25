#pragma once
#include "pattern.h"
#include <cmath>
#include "ab_color.h"

namespace RayTracer {
namespace Material {
class CheckerPattern :
  public Pattern,
  public ABColor {
 public:
  CheckerPattern() = default;

  CheckerPattern(const Color& a, const Color& b):
    ABColor(a, b) {
  }

  virtual ~CheckerPattern() {}

  Color pattern_at(const Point& p) const override {
    if (static_cast<int>(std::floor(p.x()) + std::floor(p.y()) + std::floor(p.z())) % 2 == 0) {
        return a();
    } else {
        return b();
    }
  }
};

} // end of namespace Material
} // end of namespace RayTracer
