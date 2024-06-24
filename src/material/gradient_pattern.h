#pragma once
#include "pattern.h"
#include <cmath>
#include "ab_color.h"

namespace RayTracer {
namespace Material {
class GradientPattern :
  public Pattern,
  public ABColor {
 public:
  GradientPattern() = default;

  GradientPattern(const Color& a, const Color& b):
    ABColor(a, b) {
  }

  virtual ~GradientPattern() {}

  Color pattern_at(const Point& p) const override {
    Color distance = b() - a();
    double fraction = p.x() - std::floor(p.x());

    return a() + distance * fraction;
  }
};

} // end of namespace Material
} // end of namespace RayTracer
