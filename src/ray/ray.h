#ifndef AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5
#define AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5

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

  const Point& origin() { return _origin; }
  const Point& origin() const { return _origin; }

  const Vector& direction() { return _direction; }
  const Vector& direction() const { return _direction; }

  Point position(double time) { return _origin + _direction * time; }
  Point position(double time) const { return const_cast<Ray&>(*this).position(time); }

  IntersectionCollection intersect(Shape::BasicShapePtr s);

  IntersectionCollection intersect(Shape::BasicShapePtr s) const {
    return const_cast<Ray&>(*this).intersect(s);
  }

  Ray transform(const Matrix& t) const;

 private:
  Point _origin;
  Vector _direction;
};
}  // namespace RayTracer

#endif /* AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5 */
