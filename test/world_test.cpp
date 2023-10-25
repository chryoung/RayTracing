#include <gtest/gtest.h>
#include <memory>

#include "world/world.h"
#include "light/pointlight.h"
#include "shape/sphere.h"
#include "shape/shapebuilder.h"
#include "geometry/transform.h"
#include "math/tuple.h"
#include "ray/ray.h"

using namespace RayTracer;

class WorldTest : public ::testing::Test {
protected:
  void SetUp() override {
    auto default_light = std::make_shared<Light::PointLight>(Color(1), Point(-10, 10, -10));

    default_world.light_sources().emplace_back(default_light);

    auto default_sphere_1 = Shape::ShapeBuilder::build<Shape::Sphere>();
    default_sphere_1->material()->
      set_color(Color(0.8, 1.0, 0.6))
      .set_diffuse(0.7)
      .set_specular(0.2);

    auto default_sphere_2 = Shape::ShapeBuilder::build<Shape::Sphere>();
    default_sphere_2->set_transform(Transform::scaling(0.5, 0.5, 0.5));

    default_world.objects().emplace_back(default_sphere_1);
    default_world.objects().emplace_back(default_sphere_2);
  }

  World default_world;
};

TEST_F(WorldTest, CreateAWorld) {
  World w;
  EXPECT_TRUE(w.objects().empty());
  EXPECT_TRUE(w.light_sources().empty());
}

TEST_F(WorldTest, IntersectAWorldWithARay) {
  Ray ray(Point(0, 0, -5), Vector(0, 0, 1));
  auto xs = default_world.intersect(ray);
  ASSERT_EQ(4, xs.size());
  auto iter = xs.begin();

  EXPECT_DOUBLE_EQ(4, iter->t());
  iter++;
  EXPECT_DOUBLE_EQ(4.5, iter->t());
  iter++;
  EXPECT_DOUBLE_EQ(5.5, iter->t());
  iter++;
  EXPECT_DOUBLE_EQ(6, iter->t());
  iter++;

  EXPECT_EQ(xs.end(), iter);
}
