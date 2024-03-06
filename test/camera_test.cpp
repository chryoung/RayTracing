#include "gtest/gtest.h"
#include <cmath>
#include "camera/camera.h"
#include "geometry/transform.h"
#include "world/world.h"
#include "shape/shapebuilder.h"

using namespace RayTracer;

TEST(Camera, ConstructingACamera) {
  int hsize = 160;
  int vsize = 120;
  double field_of_view = M_PI_2;
  Camera camera{hsize, vsize, field_of_view};
  EXPECT_EQ(hsize, camera.hsize());
  EXPECT_EQ(vsize, camera.vsize());
  EXPECT_DOUBLE_EQ(field_of_view, camera.field_of_view());
  EXPECT_EQ(Transform::id(), camera.transform());
}

TEST(Camera, PixelSizeForHorizontalCanvas) {
  Camera c{200, 125, M_PI_2};
  EXPECT_DOUBLE_EQ(0.01, c.pixel_size());
}

TEST(Camera, PixelSizeForVerticalCanvas) {
  Camera c{125, 200, M_PI_2};
  EXPECT_DOUBLE_EQ(0.01, c.pixel_size());
}

TEST(Camera, ConstructingARayThroughCentreOfCanvas) {
  Camera c{201, 101, M_PI_2};
  auto r = c.ray_for_pixel(100, 50);
  EXPECT_EQ(Point(0, 0, 0), r.origin());
  EXPECT_EQ(Vector(0, 0, -1), r.direction());
}

TEST(Camera, ConstructingARayThroughCornerOfCanvas) {
  Camera c{201, 101, M_PI_2};
  auto r = c.ray_for_pixel(0, 0);
  EXPECT_EQ(Point(0, 0, 0), r.origin());
  EXPECT_EQ(Vector(0.66519, 0.33259, -0.66851), r.direction());
}

TEST(Camera, ConstructingARayWhenTheCameraIsTransformed) {
  Camera c{201, 101, M_PI_2};
  c.set_transform(Transform::rotation_y(M_PI_4) * Transform::translation(0, -2, 5));
  auto r = c.ray_for_pixel(100, 50);
  EXPECT_EQ(Point(0, 2, -5), r.origin());
  const double sqrt_2_2 = ::sqrt(2) / 2;
  EXPECT_EQ(Vector(sqrt_2_2, 0, -sqrt_2_2), r.direction());
}

TEST(Camera, RenderAWorldWithACamera) {
    auto default_light = std::make_shared<Light::PointLight>(Point(-10, 10, -10), Color(1));

    World default_world;
    default_world.set_light(default_light);

    auto default_sphere_1 = Shape::ShapeBuilder::build<Shape::Sphere>();
    default_sphere_1->material()->
      set_color(Color{0.8, 1.0, 0.6})
      .set_diffuse(0.7)
      .set_specular(0.2);

    auto default_sphere_2 = Shape::ShapeBuilder::build<Shape::Sphere>();
    default_sphere_2->set_transform(Transform::scaling(0.5, 0.5, 0.5));

    default_world.objects().emplace_back(default_sphere_1);
    default_world.objects().emplace_back(default_sphere_2);

    Camera c{11, 11, M_PI_2};
    Point from(0, 0, -5);
    Point to(0, 0, 0);
    Vector up(0, 1, 0);
    c.set_transform(Transform::view_transform(from, to, up));
    Canvas image = c.render(default_world);

    EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), image.pixel_at(5, 5));
}
