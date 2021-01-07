#ifndef AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5
#define AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5

#include "tuple.h"

namespace RayTracer {
class Ray {
  Ray(double origin_x, double origin_y, double origin_z, double direction_x, double direction_y, double direction_z)
      : _origin(Tuple::make_point(origin_x, origin_y, origin_z)),
        _direction(Tuple::make_vector(direction_x, direction_y, direction_z)) {}
  Ray(const Tuple& origin, const Tuple& direction) : _origin(origin), _direction(direction) {}

  Tuple position(double time) { return _origin + _direction * time; }
  Tuple position(double time) const { return _origin + _direction * time; }

 private:
  Tuple _origin;
  Tuple _direction;
};
}  // namespace RayTracer

#endif /* AFDAB679_02C5_4C88_A3D6_F6FE8B9859D5 */
