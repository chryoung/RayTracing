#ifndef CA5A6AF1_A42B_4C61_B95B_A526A561D656
#define CA5A6AF1_A42B_4C61_B95B_A526A561D656

#include "basicshape.h"
#include "../tuple.h"

namespace RayTracer {
namespace Shape {
class Sphere : public BasicShape {
 public:
  Sphere(std::uint64_t id) : BasicShape(id), _origin(Point(0, 0, 0)) {}
  const Point& origin() { return _origin; }
  const Point& origin() const { return _origin; }
 private:
  Point _origin;
};
}  // namespace Shape

}  // namespace RayTracer

#endif /* CA5A6AF1_A42B_4C61_B95B_A526A561D656 */
