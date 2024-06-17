#include "pattern.h"
#include "shape/basicshape.h"

namespace RayTracer {
namespace Material {
Color Pattern::pattern_at_shape(std::shared_ptr<Shape::BasicShape> shape, const Point& p) {
  Point object_point = shape->transform_inv() * p;
  Point pattern_point = _transform_inv * object_point;

  return pattern_at(pattern_point);
}
}
}