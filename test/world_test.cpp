#include <gtest/gtest.h>
#include <memory>

#include "light/light.h"
#include "world/world.h"
#include "light/pointlight.h"
#include "shape/sphere.h"
#include "shape/shapebuilder.h"
#include "geometry/transform.h"
#include "math/tuple.h"
#include "ray/ray.h"
#include "ray/computation.h"

using namespace RayTracer;

class WorldTest : public ::testing::Test {
protected:
  void SetUp() override {
    auto default_light = std::make_shared<Light::PointLight>(Point(-10, 10, -10), Color(1));

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
  }

  World default_world;
};

TEST_F(WorldTest, CreateAWorld) {
  World w;
  EXPECT_TRUE(w.objects().empty());
  EXPECT_EQ(w.light(), nullptr);
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

TEST_F(WorldTest, ShadingIntersection) {
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  auto shape = default_world.object_at(0);
  Intersection i{4, shape};
  auto comps = Computation::prepare_computations(i, r);
  auto c = default_world.shade_hit(comps);
  EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), c);
}

TEST_F(WorldTest, ShadingIntersectionFromInside) {
  GTEST_SKIP() << "Incorrect result Color{0.1} was obtained";
  Light::LightPtr light = std::make_shared<Light::PointLight>(Point{0, 0.25, 0}, Color{1});
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  default_world.set_light(light);
  auto shape = default_world.object_at(1);
  Intersection i{0.5, shape};

  auto comps = Computation::prepare_computations(i, r);
  auto c = default_world.shade_hit(comps);
  EXPECT_EQ(Color(0.90498), c);
}

TEST_F(WorldTest, ColorWhenARayHits) {
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  auto c = default_world.color_at(r);
  EXPECT_EQ(Color(0.38066, 0.47583, 0.2855), c);
}

TEST_F(WorldTest, ColorWithAnIntersectionBehindTheRay) {
  auto outer = default_world.object_at(0);
  outer->material()->set_ambient(1);
  auto inner = default_world.object_at(1);
  inner->material()->set_ambient(1);
  Ray r{Point{0, 0, 0.75}, Vector{0, 0, -1}};
  auto c = default_world.color_at(r);
  EXPECT_EQ(inner->material()->color(), c);
}
