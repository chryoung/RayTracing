#pragma once
#include "geometry/transform.h"
#include "image/color.h"
#include "math/tuple.h"
#include "math/matrix.h"

namespace RayTracer {

namespace Shape {
class BasicShape;
} // end of namespace Shape

namespace Material {
class Pattern {
 public:
  Pattern(): _transform(Transform::id()), _transform_inv(_transform.inverse()) {}
  virtual ~Pattern() {}
  virtual Color color_at(const Point& p) = 0; 
  virtual Color color_at(const Point& p) const = 0; 

  virtual Color color_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p) = 0; 
  virtual Color color_at_object(std::shared_ptr<Shape::BasicShape> shape, const Point& p) const = 0; 

  const Matrix& transform() { return _transform; }
  const Matrix& transform() const { return _transform; }
  Pattern& set_transform(const Matrix& transform) {
    _transform = transform;
    _transform_inv = _transform.inverse();
    return *this;
  }

  const Matrix& transform_inv() { return _transform_inv; }
  const Matrix& transform_inv() const { return _transform_inv; }

 protected:
  Matrix _transform;
  Matrix _transform_inv;
  
};

} // end of namespace Material
} // end of namespace RayTracer

