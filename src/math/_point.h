#pragma once
#include "_tuple.h"

namespace RayTracer {
class Point : public Tuple {
 public:
  Point() : Point(0, 0, 0) {}
  Point(double x, double y, double z) : Tuple(x, y, z, Tuple::POINT_W) {}

  Point& set_w(double) override { return *this; }

  bool is_point() override { return true; }
  bool is_point() const override { return true; }
};

}  // namespace RayTracer

