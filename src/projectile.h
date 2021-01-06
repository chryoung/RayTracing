#ifndef C17184CD_A5B1_436B_956B_328159AC7BC3
#define C17184CD_A5B1_436B_956B_328159AC7BC3

#include "tuple.h"

namespace RayTracer {
class Projectile {
 public:
  Projectile(const Tuple& position, const Tuple& velocity)
      : _position(position), _velocity(velocity) {}

  Projectile(Tuple&& position, Tuple&& velocity)
    : _position(position), _velocity(velocity) {}

  const Tuple& postion() const { return _position; }
  const Tuple& postion() { return _position; }

  const Tuple& velocity() const { return _velocity; }
  const Tuple& velocity() { return _velocity; }

  Projectile& set_position(const Tuple& position) {
    _position = position;

    return *this;
  }

  Projectile& set_velocity(const Tuple& velocity) {
    _velocity = velocity;

    return *this;
  }

 private:
  Tuple _position;
  Tuple _velocity;
};
}  // namespace RayTracer

#endif /* C17184CD_A5B1_436B_956B_328159AC7BC3 */
