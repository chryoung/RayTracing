#pragma once
#include "_tuple.h"

namespace RayTracer {
class Vector : public Tuple {
 public:
  Vector() : Vector(0, 0, 0) {}
  Vector(double x, double y, double z) : Tuple(x, y, z, Tuple::VECTOR_W) {}

  Vector& set_w(double w) override { return *this; }

  bool is_vector() override { return true; }
  bool is_vector() const override { return true; }

  Vector& operator+=(const Vector& other) {
    set_x(x() + other.x());
    set_y(y() + other.y());
    set_z(z() + other.z());

    return *this;
  }

  Vector& operator-=(const Vector& other) {
    set_x(x() - other.x());
    set_y(y() - other.y());
    set_z(z() - other.z());

    return *this;
  }

  Vector operator-() const {
    return Vector(-x(), -y(), -z());
  }

  Vector cross(const Vector& other) {
    return Vector(y() * other.z() - z() * other.y(), z() * other.x() - x() * other.z(),
                  x() * other.y() - y() * other.x());
  }
};

}  // namespace RayTracer

