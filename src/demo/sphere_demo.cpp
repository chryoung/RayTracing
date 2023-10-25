#include "math/tuple.h"
#include "ray/ray.h"
#include "image/canvas.h"
#include "image/color.h"
#include "geometry/transform.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"

int main() {
  using namespace RayTracer;

  constexpr double wall_z = 10.0;
  constexpr double wall_size = 7.0;
  constexpr int canvas_pixels = 100;
  constexpr double pixel_size = wall_size / canvas_pixels;
  constexpr double half = wall_size / 2;

  auto ray_origin = Point(0, 0, -5);
  auto c = Canvas::create(canvas_pixels, canvas_pixels);
  auto color = Color(1, 0, 0);
  auto sphere = Shape::ShapeBuilder::build<Shape::Sphere>();
  Transform::TransformationBuilder tb;
  tb
    .scale(1, 0.5, 1)
    .rotate_x(M_PI / 4.0);
  sphere->set_transform(tb.build());

  for (int y = 0; y < canvas_pixels; ++y) {
    double world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; ++x) {
      double world_x = -half + pixel_size * x;
      auto position = Point(world_x, world_y, wall_z);
      Vector direction = position - ray_origin;
      direction.normalize();
      auto ray = Ray(ray_origin, direction);
      auto xs = sphere->intersect(ray);
      if (xs.hit()) {
        c.write_pixel(x, y, color);
      }
    }
  }

  c.to_file("sphere.ppm");

  return 0;
}
