#pragma once
#include "geometry/transform.h"
#include "image/color.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "shape/shapefwddecl.h"

namespace RayTracer {

namespace Shape {
class BasicShape;
} // end of namespace Shape

namespace Material {
class Pattern {
 public:
  Pattern(): _transform(Transform::id()), _transform_inv(_transform.inverse()) {}
  virtual ~Pattern() {}
  virtual Color pattern_at(const Point& p) const = 0;

  virtual Color pattern_at_shape(Shape::ConstBasicShapePtr shape, const Point& p) const;

  const Matrix& transform() const { return _transform; }
  Pattern& set_transform(const Matrix& transform) {
    _transform = transform;
    _transform_inv = _transform.inverse();
    return *this;
  }

  const Matrix& transform_inv() const { return _transform_inv; }

 protected:
  Matrix _transform;
  Matrix _transform_inv;

};

} // end of namespace Material
} // end of namespace RayTracer

