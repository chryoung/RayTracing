#pragma once
#include "pattern.h"
#include <cmath>
#include "ab_color.h"

namespace RayTracer {
namespace Material {
class RingPattern :
  public Pattern,
  public ABColor {
 public:
  RingPattern() = default;

  RingPattern(const Color& a, const Color& b):
    ABColor(a, b) {
  }

  virtual ~RingPattern() {}

  Color pattern_at(const Point& p) const override {
    if (static_cast<int>(std::floor(std::sqrt(p.x() * p.x() + p.z() * p.z()))) % 2 == 0) {
        return a();
    } else {
        return b();
    }
  }
};

} // end of namespace Material
} // end of namespace RayTracer
