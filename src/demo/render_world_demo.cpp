#include <cmath>
#include <memory>
#include "light/pointlight.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "world/world.h"
#include "camera/camera.h"
#include "geometry/transform.h"
#include "image/color.h"

int main() {
  using namespace RayTracer;

  auto floor = Shape::ShapeBuilder::build<Shape::Sphere>();
  floor->set_transform(Transform::scaling(10, 0.01, 10));
  floor->material()->set_color(Color{1, 0.9, 0.9}).set_specular(0);

  auto left_wall = Shape::ShapeBuilder::build<Shape::Sphere>();
  Transform::TransformationBuilder tb;
  tb
    .scale(10, 0.01, 10)
    .rotate_x(M_PI_2)
    .rotate_y(-M_PI_4)
    .translate(0, 0, 5);
  left_wall->set_transform(tb.build());
  left_wall->set_material(floor->material());

  auto right_wall = Shape::ShapeBuilder::build<Shape::Sphere>();
  tb
    .reset()
    .scale(10, 0.01, 10)
    .rotate_x(M_PI_2)
    .rotate_y(M_PI_4)
    .translate(0, 0, 5);
  right_wall->set_transform(tb.build());
  right_wall->set_material(floor->material());

  auto middle = Shape::ShapeBuilder::build<Shape::Sphere>();
  middle->set_transform(Transform::translation(-0.5, 1, 0.5));
  middle->material()
    ->set_color(Color{0.1, 1, 0.5})
    .set_diffuse(0.7)
    .set_specular(0.3);

  auto right = Shape::ShapeBuilder::build<Shape::Sphere>();
  tb
    .reset()
    .scale(0.5, 0.5, 0.5)
    .translate(1.5, 0.5, -0.5);
  right->set_transform(tb.build());
  right->material()
    ->set_color(Color{0.5, 1, 0.1})
    .set_diffuse(0.7)
    .set_specular(0.3);

  auto left = Shape::ShapeBuilder::build<Shape::Sphere>();
  tb
    .reset()
    .scale(0.33, 0.33, 0.33)
    .translate(-1.5, 0.33, -0.75);
  left->set_transform(tb.build());
  left->material()
    ->set_color(Color{1, 0.8, 0.1})
    .set_diffuse(0.7)
    .set_specular(0.3);

  Camera camera{1000, 500, M_PI / 3};
  camera.set_transform(Transform::view_transform(Point{0, 1.5, -5}, Point{0, 1, 0}, Vector{0, 1, 0}));

  World world;
  world
    .set_light(std::make_shared<Light::PointLight>(Point{-10, 10, -10}, Color{1}))
    .add_object(floor)
    .add_object(left_wall)
    .add_object(right_wall)
    .add_object(middle)
    .add_object(right)
    .add_object(left);

  auto canvas = camera.render(world);

  canvas.to_file("first_world.ppm");

  return 0;
}
