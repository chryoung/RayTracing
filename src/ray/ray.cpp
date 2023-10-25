#include "ray.h"

#include <memory>

#include "shape/basicshape.h"
#include "shape/sphere.h"

namespace RayTracer {
Ray Ray::transform(const Matrix& t) const {
  return Ray(t * origin(), t * direction());
}
}  // namespace RayTracer
