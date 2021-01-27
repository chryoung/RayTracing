#include "ray.h"

namespace RayTracer {
IntersectionCollection Ray::intersect(std::shared_ptr<Shape::Sphere> s) {
  IntersectionCollection intersections;

  auto sphere_to_ray = origin() - s->origin();
  auto a = direction().dot(direction());
  auto b = 2 * direction().dot(sphere_to_ray);
  auto c = sphere_to_ray.dot(sphere_to_ray) - 1;

  double discriminant = b * b - 4 * a * c;
  if (is_double_ge(discriminant, 0.0)) {
    double sqrt_discriminant = sqrt(discriminant);
    double double_a = 2 * a;
    double t1 = (-b - sqrt_discriminant) / double_a;
    double t2 = (-b + sqrt_discriminant) / double_a;
    intersections.insert(Intersection(t1, s));
    intersections.insert(Intersection(t2, s));
  }

  return intersections;
}
}  // namespace RayTracer