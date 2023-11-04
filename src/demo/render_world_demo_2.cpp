#include <cmath>
#include <memory>
#include "light/pointlight.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "shape/plane.h"
#include "world/world.h"
#include "camera/camera.h"
#include "geometry/transform.h"
#include "image/color.h"

int main() {
  using namespace RayTracer;

  Transform::TransformationBuilder tb;

  auto floor = Shape::ShapeBuilder::build<Shape::Plane>();
  floor->material()->set_color(Color{1, 0.9, 0.9}).set_specular(0);

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
    .add_object(middle)
    .add_object(right)
    .add_object(left);

  auto canvas = camera.render(world);

  canvas.to_file("world_with_plane.ppm");

  return 0;
}
