#include "world.h"

namespace RayTracer {
IntersectionCollection World::intersect(const Ray& ray) {
  IntersectionCollection union_intersection;
  for (auto& object : _objects) {
    auto xs = ray.intersect(object);
    for (const auto& x : xs) {
      union_intersection.insert(x);
    }
  }

  return union_intersection;
}

} /* RayTracer  */ 
