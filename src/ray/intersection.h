#ifndef DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7
#define DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7

#include <memory>

#include "shape/basicshape.h"

namespace RayTracer {
class Intersection {
 public:
  Intersection(double time, std::shared_ptr<Shape::BasicShape> object) : _object(object), _time(time) {}

  std::shared_ptr<Shape::BasicShape> object() { return _object; }
  std::shared_ptr<Shape::BasicShape> object() const { return _object; }

  double time() { return _time; }
  double time() const { return _time; }

 private:
  std::shared_ptr<Shape::BasicShape> _object;
  double _time;
};
}  // namespace RayTracer

#endif /* DC7A1CB1_389F_4A58_B81C_8E3E52BE56A7 */
