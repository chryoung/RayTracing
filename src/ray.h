#ifndef AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5
#define AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5

#include <vector>
#include <cmath>

#include "shape/sphere.h"
#include "tuple.h"
#include "utility.h"

namespace RayTracer {
class Ray {
 public:
  Ray(double origin_x, double origin_y, double origin_z, double direction_x, double direction_y, double direction_z)
      : _origin(Point(origin_x, origin_y, origin_z)), _direction(Vector(direction_x, direction_y, direction_z)) {}
  Ray(const Point& origin, const Vector& direction) : _origin(origin), _direction(direction) {}

  const Point& origin() { return _origin; }
  const Point& origin() const { return _origin; }

  const Vector& direction() { return _direction; }
  const Vector& direction() const { return _direction; }

  Point position(double time) { return _origin + _direction * time; }
  Point position(double time) const { return _origin + _direction * time; }

  std::vector<double> intersect(const Shape::Sphere& s) {
    std::vector<double> roots;

    auto sphere_to_ray = origin() - s.origin();
    auto a = direction().dot(direction());
    auto b = 2 * direction().dot(sphere_to_ray);
    auto c = sphere_to_ray.dot(sphere_to_ray) - 1;

    double discriminant = b * b - 4 * a * c;
    if (is_double_ge(discriminant, 0.0)) {
      double sqrt_discriminant = sqrt(discriminant);
      double double_a = 2 * a;
      double t1 = (-b - sqrt_discriminant) / double_a;
      double t2 = (-b + sqrt_discriminant) / double_a;
      roots.emplace_back(t1);
      roots.emplace_back(t2);
    }

    return roots;
  }

  std::vector<double> intersect(const Shape::Sphere& s) const {
    return const_cast<Ray&>(*this).intersect(s);
  }

 private:
  Point _origin;
  Vector _direction;
};
}  // namespace RayTracer

#endif /* AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5 */
