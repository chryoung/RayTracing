#include "sphere.h"
#include <iostream>

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
}  // namespace Shape

}  // namespace RayTracer
