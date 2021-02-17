#ifndef CA5A6AF1_A42B_4C61_B95B_A526A561D656
#define CA5A6AF1_A42B_4C61_B95B_A526A561D656

#include "basicshape.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "geometry/transform.h"

namespace RayTracer {
namespace Shape {
class ShapeBuilder;
class Sphere : public BasicShape {
 public:
  const Point& origin() { return _origin; }
  const Point& origin() const { return _origin; }

  Matrix transform() const { return _transform; }
  Sphere& set_transform(const Matrix& t) {
    _transform = t;

    return *this;
  }

  friend class ShapeBuilder;

 private:
  explicit Sphere(std::uint64_t id) : 
    BasicShape(id),
    _origin(Point(0, 0, 0)),
    _transform(Matrix::id(Transform::TRANSFORMATION_MATRIX_ROWS)) {}
  Point _origin;
  Matrix _transform;
};
}  // namespace Shape

}  // namespace RayTracer

#endif /* CA5A6AF1_A42B_4C61_B95B_A526A561D656 */
