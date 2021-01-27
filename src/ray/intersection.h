#ifndef DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7
#define DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7

#include <memory>
#include <ostream>

#include "shape/basicshape.h"

namespace RayTracer {
class Intersection {
 public:
  Intersection(double time, Shape::BasicShapePtr object) : _object(object), _time(time) {}

  Shape::BasicShapePtr object() { return _object; }
  Shape::BasicShapePtr object() const { return _object; }

  double time() { return _time; }
  double time() const { return _time; }

 private:
  Shape::BasicShapePtr _object;
  double _time;
};

inline bool operator==(const Intersection& a, const Intersection& b) {
  return a.time() == b.time() && a.object() == b.object();
}

inline bool operator!=(const Intersection& a, const Intersection& b) { return !(a == b); }

inline std::ostream& operator<<(std::ostream& out, const Intersection& a) {
  out << "t = " << a.time() << ", object ID == " << a.object()->id();
  return out;
}

}  // namespace RayTracer

#endif /* DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7 */
