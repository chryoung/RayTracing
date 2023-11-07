#include "camera.h"
#include <cmath>
#include "utility/utility.h"

namespace RayTracer {
void Camera::update_computed_data() {
  double half_view = ::tan(_field_of_view / 2.0);
  double aspect = static_cast<double>(_hsize) / _vsize;
  if (is_double_ge(aspect, 1.0)) {
    _half_width = half_view;
    _half_height = half_view / aspect;
  } else {
    _half_width = half_view * aspect;
    _half_height = half_view;
  }

  _pixel_size = (_half_width * 2) / _hsize;
}

Ray Camera::ray_for_pixel(int px, int py) {
  double xoffset = (static_cast<double>(px) + 0.5) * _pixel_size;
  double yoffset = (static_cast<double>(py) + 0.5) * _pixel_size;

  double world_x = _half_width - xoffset;
  double world_y = _half_height - yoffset;

  Point pixel = _transform_inv * Point(world_x, world_y, -1);
  Point origin = _transform_inv * Point(0, 0, 0);
  Vector direction = pixel - origin;
  direction.normalize();

  return Ray(origin, direction);
}

Canvas Camera::render(const World& w) {
  Canvas image = Canvas::create(_hsize, _vsize);

  for (int y = 0; y < _vsize; ++y) {
    for (int x = 0; x < _hsize; ++x) {
      Ray ray = ray_for_pixel(x, y);
      Color color = w.color_at(ray);
      image.write_pixel(x, y, color);
    }
  }

  return image;
}
} /* RayTracer  */ 
