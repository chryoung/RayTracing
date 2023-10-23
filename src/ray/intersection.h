#ifndef DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7
#define DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7

#include <memory>
#include <ostream>

#include "shape/basicshape.h"

namespace RayTracer {
class Intersection {
 public:
  Intersection(double t, Shape::BasicShapePtr object) : _object(object), _t(t) {}

  Shape::BasicShapePtr object() { return _object; }
  const Shape::BasicShapePtr& object() const { return _object; }

  double t() { return _t; }
  double t() const { return _t; }

 private:
  Shape::BasicShapePtr _object;
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

#endif /* DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7 */
