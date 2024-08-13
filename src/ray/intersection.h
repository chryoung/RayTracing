#pragma once
#include <memory>
#include <ostream>

#include "shape/basicshape.h"

namespace RayTracer {
class Intersection {
 public:
  Intersection(double t, Shape::ConstBasicShapePtr object) : _object(object), _t(t) {}

  Shape::ConstBasicShapePtr object() const { return _object; }

  double t() const { return _t; }

 private:
  Shape::ConstBasicShapePtr _object;
  double _t;
};

inline bool operator==(const Intersection& a, const Intersection& b) {
  return a.t() == b.t() && a.object() == b.object();
}

inline bool operator!=(const Intersection& a, const Intersection& b) { return !(a == b); }

inline std::ostream& operator<<(std::ostream& out, const Intersection& a) {
  out << "t = " << a.t() << ", object ID == " << a.object()->id();
  return out;
}

}  // namespace RayTracer

