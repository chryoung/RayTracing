#pragma once
#include "math/tuple.h"

namespace RayTracer {
class Projectile {
 public:
  Projectile(const Point& position, const Vector& velocity) : _position(position), _velocity(velocity) {}

  Projectile(Point&& position, Vector&& velocity) : _position(position), _velocity(velocity) {}

  const Point& postion() const { return _position; }

  const Vector& velocity() const { return _velocity; }

  Projectile& set_position(const Point& position) {
    _position = position;

    return *this;
  }

  Projectile& set_velocity(const Vector& velocity) {
    _velocity = velocity;

    return *this;
  }

 private:
  Point _position;
  Vector _velocity;
};
}  // namespace RayTracer

