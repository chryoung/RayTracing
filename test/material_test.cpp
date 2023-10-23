#include <gtest/gtest.h>
#include <cmath>

#include "math/tuple.h"
#include "light/pointlight.h"
#include "material/phong.h"
#include "image/color.h"


using namespace RayTracer;

class MaterialTest: public testing::Test {
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
  Light::PointLight light{white, Point{0, 0, -10}};
  Material::PhongMaterial m;

  auto result = m.lighting(light, position, eyev, normalv);
  EXPECT_EQ(Color(1.9), result);
}

TEST_F(MaterialTest, LightingWithEyeBetweenLightAndSurfaceEyeOffset45) {
  const double x = sqrt(2.0) / 2.0;
  Vector eyev{0, x, -x};
  Light::PointLight light{white, Point{0, 0, -10}};
  Material::PhongMaterial m;

  auto result = m.lighting(light, position, eyev, normalv);
  EXPECT_EQ(Color(1), result);
}

TEST_F(MaterialTest, LightingWithEyeBetweenLightAndSurfaceLightOffset45) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{white, Point{0, 10, -10}};
  Material::PhongMaterial m;

  auto result = m.lighting(light, position, eyev, normalv);
  EXPECT_EQ(Color(0.7364), result);
}

TEST_F(MaterialTest, LightingWithEyeInThePathOfTheReflection) {
  const double x = sqrt(2.0) / 2.0;
  Vector eyev{0, -x, -x};
  Light::PointLight light{white, Point{0, 10, -10}};
  Material::PhongMaterial m;

  auto result = m.lighting(light, position, eyev, normalv);
  EXPECT_EQ(Color(1.6364), result);
}

TEST_F(MaterialTest, LightingWithLightBehindSurface) {
  Vector eyev{0, 0, -1};
  Light::PointLight light{white, Point{0, 0, 10}};
  Material::PhongMaterial m;

  auto result = m.lighting(light, position, eyev, normalv);
  EXPECT_EQ(Color(0.1), result);
}
