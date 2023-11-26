#include "stripe_pattern.h"
#include "shape/basicshape.h"

namespace RayTracer {
namespace Material {
Color StripePattern::stripe_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p) {
  Point object_point = shape->transform_inv() * p;
  Point pattern_point = _transform_inv * object_point;

  return stripe_at(pattern_point);
}

} // end of namespace Material
} // end of namespace RayTracer
