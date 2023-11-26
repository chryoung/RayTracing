#include <gtest/gtest.h>
#include <cmath>

#include "math/tuple.h"
#include "light/pointlight.h"
#include "material/phong.h"
#include "image/color.h"
#include "material/stripe_pattern.h"
#include "shape/sphere.h"
#include "shape/shapebuilder.h"


using namespace RayTracer;

class MaterialTest : public ::testing::Test {
protected:
  void SetUp() override {
    normalv = Vector{0, 0, -1};
    position = Point{0, 0, 0};
    white = Color{1, 1, 1};
  }

  Vector normalv;
  Point position;
  Color white;
};

TEST_F(MaterialTest, DefaultMaterial) {
  Material::PhongMaterial m;
  EXPECT_EQ(Color(1, 1, 1), m.color());
  EXPECT_DOUBLE_EQ(0.1, m.ambient());
  EXPECT_DOUBLE_EQ(0.9, m.diffuse());
  EXPECT_DOUBLE_EQ(0.9, m.specular());
  EXPECT_DOUBLE_EQ(200.0, m.shininess());
}

TEST_F(MaterialTest, LightingWithEyeBetweenLightAndSurface) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{Point{0, 0, -10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, false);
  EXPECT_EQ(Color(1.9), result);
}

TEST_F(MaterialTest, LightingWithEyeBetweenLightAndSurfaceEyeOffset45) {
  const double x = sqrt(2.0) / 2.0;
  Vector eyev{0, x, -x};
  Light::PointLight light{Point{0, 0, -10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, false);
  EXPECT_EQ(Color(1), result);
}

TEST_F(MaterialTest, LightingWithEyeBetweenLightAndSurfaceLightOffset45) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{Point{0, 10, -10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, false);
  EXPECT_EQ(Color(0.7364), result);
}

TEST_F(MaterialTest, LightingWithEyeInThePathOfTheReflection) {
  const double x = sqrt(2.0) / 2.0;
  Vector eyev{0, -x, -x};
  Light::PointLight light{Point{0, 10, -10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, false);
  EXPECT_EQ(Color(1.6364), result);
}

TEST_F(MaterialTest, LightingWithLightBehindSurface) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{Point{0, 0, 10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, false);
  EXPECT_EQ(Color(0.1), result);
}

TEST_F(MaterialTest, LightingWithSurfaceInShadow) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{Point{0, 0, -10}, white};
  Material::PhongMaterial m;

  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto result = m.lighting(object, light, position, eyev, normalv, true);
  EXPECT_EQ(Color(0.1), result);
}

TEST_F(MaterialTest, LightingWithAPatternApplied) {
  Material::PhongMaterial m;
  m.set_pattern(std::make_shared<Material::StripePattern>())
    .set_ambient(1)
    .set_diffuse(0)
    .set_specular(0);
  Vector eyev{0, 0, -1};
  Light::PointLight light{Point{0, 0, -10}, Color{1, 1, 1}};
  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto c1 = m.lighting(object, light, Point{0.9, 0, 0}, eyev, normalv, false);
  auto c2 = m.lighting(object, light, Point{1.1, 0, 0}, eyev, normalv, false);

  EXPECT_EQ(Color{1}, c1);
  EXPECT_EQ(Color{0}, c2);
}
