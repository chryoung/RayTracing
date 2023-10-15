#include "math/tuple.h"
#include "ray/ray.h"
#include "image/canvas.h"
#include "image/color.h"
#include "geometry/transform.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "material/phong.h"
#include "light/pointlight.h"

#ifdef DEBUG
#include <iostream>
using std::cout;
#define DEBUG(x) (cout << #x << " = " << (x) << "\n")
#else
#define DEBUG(x)
#endif


int main() {
  using namespace RayTracer;

  constexpr double wall_z = 10.0;
  constexpr double wall_size = 7.0;
  constexpr int canvas_pixels = 100;
  constexpr double pixel_size = wall_size / canvas_pixels;
  constexpr double half = wall_size / 2;

  auto ray_origin = Point(0, 0, -5);
  auto c = Canvas::create(canvas_pixels, canvas_pixels);
  auto sphere = Shape::ShapeBuilder::build<Shape::Sphere>();
  Transform::TransformationBuilder tb;
  tb
    .scale(1, 0.5, 1)
    .rotate_x(M_PI / 4.0);
  // sphere->set_transform(tb.build());
  sphere->set_material(Material::PhongMaterial());
  sphere->material().set_color(Color(1, 0.2, 1));

  auto light = Light::PointLight(Color(1), Point(-10, 10, -10));
  const Color black = Color::make_black();

  for (int y = 0; y < canvas_pixels; ++y) {
    double world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; ++x) {
      double world_x = -half + pixel_size * x;
      auto position = Point(world_x, world_y, wall_z);
      Vector direction = position - ray_origin;
      direction.normalize();
      auto ray = Ray(ray_origin, direction);
      auto xs = ray.intersect(sphere);
      auto hit = xs.hit();
      if (hit) {
        DEBUG(hit->t());
        auto point = ray.position(hit->t());
        DEBUG(point);
        auto normal = hit->object()->normal_at(point);
        DEBUG(normal);
        const auto& eye = ray.direction();
        auto color = hit->object()->material().lighting(light, point, eye, normal);
        c.write_pixel(x, y, color);
      } else {
        c.write_pixel(x, y, black);
      }
    }
  }

  c.to_file("sphere.ppm");

  return 0;
}
