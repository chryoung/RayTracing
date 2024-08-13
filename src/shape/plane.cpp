#include "plane.h"
#include <cmath>
#include "ray/ray.h"
#include "ray/intersection_collection.h"
#include "utility/utility.h"

namespace RayTracer {
namespace Shape {
Vector Plane::local_normal_at(const Point& local_point) const {
  return Vector{0, 1, 0};
}

IntersectionCollection Plane::local_intersect(const Ray& local_test_ray) const {
  if (std::fabs(local_test_ray.direction().y()) < DOUBLE_EPSILON) {
    return IntersectionCollection{};
  }

  double t = -local_test_ray.origin().y() / local_test_ray.direction().y();

  IntersectionCollection xs;
  xs.insert(Intersection{t, shared_from_this()});

  return xs;
}
} /* Shape */ 
} /* RayTracer  */ 
