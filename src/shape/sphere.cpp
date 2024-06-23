#include "sphere.h"
#include <iostream>
#include <memory>
#include "ray/ray.h"
#include "ray/intersection.h"
#include "ray/intersection_collection.h"
#include "shape/basicshape.h"

namespace RayTracer {
namespace Shape {
Vector Sphere::local_normal_at(const Point& p) const {
  return p - _origin;
}

IntersectionCollection Sphere::local_intersect(const Ray& local_test_ray) const {
  IntersectionCollection intersections;

    auto sphere_to_ray = local_test_ray.origin() - origin();
    auto a = local_test_ray.direction().dot(local_test_ray.direction());
    auto b = 2 * local_test_ray.direction().dot(sphere_to_ray);
    auto c = sphere_to_ray.dot(sphere_to_ray) - 1;

    double discriminant = b * b - 4 * a * c;
    if (is_double_ge(discriminant, 0.0)) {
      double sqrt_discriminant = sqrt(discriminant);
      double double_a = 2 * a;
      double t1 = (-b - sqrt_discriminant) / double_a;
      double t2 = (-b + sqrt_discriminant) / double_a;
      intersections.insert(Intersection(t1, shared_from_this()));
      intersections.insert(Intersection(t2, shared_from_this()));
    }

  return intersections;
}

}  // namespace Shape
}  // namespace RayTracer
