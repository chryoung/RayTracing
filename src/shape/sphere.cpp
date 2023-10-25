#include "sphere.h"
#include <iostream>
#include <memory>
#include "ray/ray.h"
#include "ray/intersection.h"
#include "ray/intersection_collection.h"
#include "shape/basicshape.h"

namespace RayTracer {
namespace Shape {
Vector Sphere::normal_at(const Point& world_point) {
  auto object_point = transform().inverse() * world_point;
  auto object_normal = object_point - _origin;
  auto world_normal = transform().inverse().transpose() * object_normal;
  world_normal.set_w(0);
  world_normal.normalize();

  return world_normal;
}

IntersectionCollection Sphere::intersect(const Ray& ray) {
  IntersectionCollection intersections;

    auto test_ray = ray.transform(transform().inverse());
    auto sphere_to_ray = test_ray.origin() - origin();
    auto a = test_ray.direction().dot(test_ray.direction());
    auto b = 2 * test_ray.direction().dot(sphere_to_ray);
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

IntersectionCollection Sphere::intersect(const Ray& ray) const {
  return const_cast<Sphere&>(*this).intersect(ray);
}

}  // namespace Shape

}  // namespace RayTracer
