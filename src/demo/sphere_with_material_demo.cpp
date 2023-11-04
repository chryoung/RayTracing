#include <memory>
#include "math/tuple.h"
#include "ray/ray.h"
#include "image/canvas.h"
#include "image/color.h"
#include "geometry/transform.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "material/phong.h"
#include "light/pointlight.h"

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
    .rotate_z(M_PI / 4.0);
  sphere->set_transform(tb.build());
  sphere->set_material(std::make_shared<Material::PhongMaterial>());
  sphere->material()->set_color(Color(1, 0.2, 1));

  auto light = Light::PointLight(Point(-10, 10, -10), Color(1));
  const Color BLACK = Color::make_black();

  for (int y = 0; y < canvas_pixels; ++y) {
    double world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; ++x) {
      double world_x = -half + pixel_size * x;
      auto position = Point(world_x, world_y, wall_z);
      Vector direction = position - ray_origin;
      direction.normalize();
      auto ray = Ray(ray_origin, direction);
      auto xs = sphere->intersect(ray);
      auto hit = xs.hit();
      if (hit) {
        auto point = ray.position(hit->t());
        auto normal = hit->object()->normal_at(point);
        const auto& eye = ray.direction();
        auto color = hit->object()->material()->lighting(light, point, eye, normal, false);
        c.write_pixel(x, y, color);
      } else {
        c.write_pixel(x, y, BLACK);
      }
    }
  }

  c.to_file("sphere_with_material_demo.ppm");

  return 0;
}
