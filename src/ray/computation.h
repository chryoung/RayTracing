#pragma once
#include "math/tuple.h"
#include "shape/basicshape.h"
#include "ray/ray.h"
#include "ray/intersection.h"
#include "utility/utility.h"

namespace RayTracer {
struct Computation {
  double t;
  bool inside;
  Shape::ConstBasicShapePtr object;
  Point point;
  Point over_point;
  Vector eyev;
  Vector normalv;
  Vector reflectv;

  static Computation prepare_computations(const Intersection& i, const Ray& r);
};

} /* RayTracer  */

