#pragma once
#include <memory>
#include "math/matrix.h"
#include "geometry/transform.h"
#include "ray/ray.h"
#include "world/world.h"
#include "image/canvas.h"

namespace RayTracer {

class Camera {
public:
  Camera(): _transform{Transform::id()},
    _transform_inv{_transform.inverse()}
  {
    update_computed_data();
  }

  Camera(int hsize, int vsize, double field_of_view):
    _hsize(hsize),
    _vsize(vsize),
    _field_of_view(field_of_view),
    _transform{Transform::id()},
    _transform_inv{_transform.inverse()}
  {
    update_computed_data();
  }


  Camera& set_hsize(int hsize) {
    _hsize = hsize;
    update_computed_data();

    return *this;
  }

  Camera& set_vsize(int vsize) {
    _vsize = vsize;
    update_computed_data();

    return *this;
  }

  Camera& set_transform(const Matrix& t) {
    _transform = t;
    _transform_inv = t.inverse();

    return *this;
  }

  Camera& set_transform(Matrix&& t) {
    _transform = std::move(t);
    _transform_inv = _transform.inverse();

    return *this;
  }

  double hsize() { return _hsize; }
  double hsize() const { return _hsize; }
  double vsize() { return _vsize; }
  double vsize() const { return _vsize; }
  double field_of_view() { return _field_of_view; }
  double field_of_view() const { return _field_of_view; }
  double pixel_size() { return _pixel_size; }
  double pixel_size() const { return _pixel_size; }
  Matrix& transform() { return _transform; }
  const Matrix& transform() const { return _transform; }

  Ray ray_for_pixel(int px, int py);
  Canvas render(const World& w);

private:
  void update_computed_data();

private:
  int _hsize = 0;
  int _vsize = 0;
  double _field_of_view = 0;
  double _half_width;
  double _half_height;
  double _pixel_size;
  Matrix _transform;
  Matrix _transform_inv;
};
  
} /* RayTracer  */ 

