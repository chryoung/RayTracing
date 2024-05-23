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
  Shape::BasicShapePtr object;
  Point point;
  Point over_point;
  Vector eyev;
  Vector normalv;

  static Computation prepare_computations(const Intersection& i, const Ray& r);
};
  
} /* RayTracer  */ 

