#pragma once
#include <cmath>
#include <memory>
#include <vector>

#include "intersection.h"
#include "intersection_collection.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "shape/sphere.h"
#include "utility/utility.h"

namespace RayTracer {
class Ray {
 public:
  Ray(double origin_x, double origin_y, double origin_z, double direction_x, double direction_y, double direction_z)
      : _origin(Point(origin_x, origin_y, origin_z)), _direction(Vector(direction_x, direction_y, direction_z)) {}
  Ray(const Point& origin, const Vector& direction) : _origin(origin), _direction(direction) {}

  const Point& origin() const { return _origin; }

  const Vector& direction() const { return _direction; }

  Point position(double time) const { return _origin + _direction * time; }

  Ray transform(const Matrix& t) const;

 private:
  Point _origin;
  Vector _direction;
};
}  // namespace RayTracer

