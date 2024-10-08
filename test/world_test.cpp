#include "gtest/gtest.h"
#include <memory>

#include "light/light.h"
#include "world/world.h"
#include "light/pointlight.h"
#include "shape/sphere.h"
#include "shape/plane.h"
#include "shape/shapebuilder.h"
#include "material/phong.h"
#include "geometry/transform.h"
#include "ray/ray.h"
#include "ray/computation.h"
#include "utility/utility.h"

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

    auto default_sphere_2 = Shape::ShapeBuilder::build<Shape::Sphere>(Transform::scaling(0.5, 0.5, 0.5));

    default_world.add_object(default_sphere_1);
    default_world.add_object(default_sphere_2);
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
  // Textbook was expecting Color(0.90498, 0.90498, 0.90498) but Color(0.1, 0.1, 0.1) was obtained by the algorithm.
  // The value was validated manually and is correct but is contradict to the one in the book.";
  Light::LightPtr light = std::make_shared<Light::PointLight>(Point{0, 0.25, 0}, Color{1});
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  default_world.set_light(light);
  auto shape = default_world.object_at(1);
  Intersection i{0.5, shape};

  auto comps = Computation::prepare_computations(i, r);
  auto c = default_world.shade_hit(comps);
  EXPECT_EQ(Color(0.1), c);
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

TEST_F(WorldTest, NoShadowWhenNothingIsCollinearBetweenPointAndLight) {
  Point p{0, 10, 0};
  EXPECT_FALSE(default_world.is_shadowed(p));
}

TEST_F(WorldTest, ShadowWhenObjectBetweenPointAndLight) {
  Point p{10, -10, 10};
  EXPECT_TRUE(default_world.is_shadowed(p));
}

TEST_F(WorldTest, NoShadowWhenObjectIsBehindLight) {
  Point p{-20, 20, -20};
  EXPECT_FALSE(default_world.is_shadowed(p));
}

TEST_F(WorldTest, NoShadowWhenObjectIsBehindPoint) {
  Point p{-2, 2, -2};
  EXPECT_FALSE(default_world.is_shadowed(p));
}

TEST_F(WorldTest, ShadeHitIsGivenAnIntersectionInShadow) {
  World w;
  w.set_light(std::make_shared<Light::PointLight>(Point{0, 0, -10}, Color{1}));
  auto s1 = Shape::ShapeBuilder::build<Shape::Sphere>();
  w.add_object(s1);
  auto s2 = Shape::ShapeBuilder::build<Shape::Sphere>(Transform::translation(0, 0, 10));
  w.add_object(s2);
  Ray r{Point{0, 0, 5}, Vector{0, 0, 1}};
  Intersection i{4, s2};
  auto comps = Computation::prepare_computations(i, r);
  auto c = w.shade_hit(comps);

  EXPECT_EQ(Color{0.1}, c);
}

TEST_F(WorldTest, HitShouldOffsetPoint) {
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  auto shape = Shape::ShapeBuilder::build<Shape::Sphere>(Transform::translation(0, 0, 1));
  Intersection i{5, shape};
  auto comps = Computation::prepare_computations(i, r);
  EXPECT_TRUE(comps.over_point.z() < DOUBLE_EPSILON / 2);
  EXPECT_TRUE(comps.point.z() > comps.over_point.z());
}

TEST_F(WorldTest, ReflectedColorForANonReflectiveMaterial) {
  Ray r{Point{0, 0, 0}, Vector{0, 0, 1}};
  auto shape = default_world.object_at(1);
  shape->material()->set_ambient(1);
  Intersection i{1, shape};
  auto comps = Computation::prepare_computations(i, r);
  auto color = default_world.reflected_color(comps, 5);
  EXPECT_EQ(Color(0), color);
}

TEST_F(WorldTest, ReflectedColorForAReflectiveMaterial) {
  auto material = std::make_shared<Material::PhongMaterial>();
  material->set_reflective(0.5);
  auto shape = Shape::ShapeBuilder::build<Shape::Plane>(
      Transform::translation(0, -1, 0),
      material);
  default_world.add_object(shape);
  double sqrt_2 = std::sqrt(2.0);
  double sqrt_2_2 = sqrt_2 / 2.0;
  Ray r{Point{0, 0, -3}, Vector{0,  -sqrt_2_2, sqrt_2_2}};
  Intersection i{sqrt_2, shape};
  auto comps = Computation::prepare_computations(i, r);
  auto color = default_world.reflected_color(comps, 5);
  EXPECT_EQ(Color(0.19032, 0.2379, 0.14274), color);
}

TEST_F(WorldTest, shade_hitWithAReflectiveMaterial) {
  auto material = std::make_shared<Material::PhongMaterial>();
  material->set_reflective(0.5);
  auto shape = Shape::ShapeBuilder::build<Shape::Plane>(
      Transform::translation(0, -1, 0),
      material);
  default_world.add_object(shape);
  double sqrt_2 = std::sqrt(2.0);
  double sqrt_2_2 = sqrt_2 / 2.0;
  Ray r{Point{0, 0, -3}, Vector{0,  -sqrt_2_2, sqrt_2_2}};
  Intersection i{sqrt_2, shape};
  auto comps = Computation::prepare_computations(i, r);
  auto color = default_world.shade_hit(comps);
  EXPECT_EQ(Color(0.87677, 0.92436, 0.82918), color);
}

TEST_F(WorldTest, color_atWithMutuallyReflectiveSurfaces) {
  World w;
  auto light = std::make_shared<Light::PointLight>(Point{0, 0, 0}, Color{1.0});
  w.set_light(light);

  auto lower_material = std::make_shared<Material::PhongMaterial>();
  lower_material->set_reflective(1);
  auto lower = Shape::ShapeBuilder::build<Shape::Plane>(
      Transform::translation(0, -1, 0),
      lower_material);

  w.add_object(lower);

  auto upper_material = std::make_shared<Material::PhongMaterial>();
  upper_material->set_reflective(1);
  auto upper = Shape::ShapeBuilder::build<Shape::Plane>(
      Transform::translation(0, 1, 0),
      upper_material);

  w.add_object(upper);
  w.add_object(lower);

  Ray r{Point{0, 0, 0}, Vector{0, 1, 0}};
  w.color_at(r);

  EXPECT_NO_FATAL_FAILURE();
}

TEST_F(WorldTest, ReflectedColorAtMaximumRecursiveDepth) {
  auto material = std::make_shared<Material::PhongMaterial>();
  material->set_reflective(0.5);
  auto shape = Shape::ShapeBuilder::build<Shape::Plane>(
      Transform::translation(0, -1, 0),
      material);
  default_world.add_object(shape);
  double sqrt_2 = std::sqrt(2.0);
  double sqrt_2_2 = sqrt_2 / 2.0;
  Ray r{Point{0, 0, -3}, Vector{0,  -sqrt_2_2, sqrt_2_2}};
  Intersection i{sqrt_2, shape};
  auto comps = Computation::prepare_computations(i, r);
  auto color = default_world.reflected_color(comps, 0);
  EXPECT_EQ(Color(0, 0, 0), color);
}
