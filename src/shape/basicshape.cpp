#include "basicshape.h"
#include "ray/intersection_collection.h"
#include "ray/ray.h"

namespace RayTracer {
namespace Shape
{
  
IntersectionCollection BasicShape::intersect(const Ray& ray) const {
  return const_cast<BasicShape&>(*this).intersect(ray);
}

IntersectionCollection BasicShape::intersect(const Ray& ray) {
    auto local_test_ray = ray.transform(_transform_inv);

    return local_intersect(local_test_ray);
}

Vector BasicShape::normal_at(const Point& p) const {
  return const_cast<BasicShape&>(*this).normal_at(p);
}

Vector BasicShape::normal_at(const Point& p) {
  auto local_point = _transform_inv * p;
  auto local_normal = local_normal_at(local_point);
  auto world_normal = _transform_inv_t * local_normal;
  world_normal.set_w(0);
  world_normal.normalize();

  return world_normal;
}

Vector BasicShape::local_normal_at(const Point& local_point) {
  return Vector{};
}

IntersectionCollection BasicShape::local_intersect(const Ray& local_test_ray) {
  return IntersectionCollection{};
}

} /* Shape */ 
} /* RayTracer  */ 

