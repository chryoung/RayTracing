#include "material/material.h"
#include "shape/sphere.h"

#include <cmath>
#include <memory>
#include <gtest/gtest.h>

#include "shape/shapebuilder.h"
#include "geometry/transform.h"
#include "math/matrix.h"
#include "math/tuple.h"
#include "material/phong.h"

using namespace RayTracer;

TEST(Sphere, WhenCreateSphereExpectHasIdTransformation) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  EXPECT_EQ(Transform::id(), s->transform());
}

TEST(Sphere, WhenSetTransformExpectTransform) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto t = Transform::translation(2,3,4);
  s->set_transform(t);
  EXPECT_EQ(t, s->transform());
}

TEST(Sphere, WhenNormalOnSphereAtXAxisExpectNormal) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto n = s->normal_at(Point(1, 0, 0));
  EXPECT_EQ(Vector(1, 0, 0), n);
}

TEST(Sphere, WhenNormalOnSphereAtYAxisExpectNormal) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto n = s->normal_at(Point(0, 1, 0));
  EXPECT_EQ(Vector(0, 1, 0), n);
}

TEST(Sphere, WhenNormalOnSphereAtZAxisExpectNormal) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto n = s->normal_at(Point(0, 0, 1));
  EXPECT_EQ(Vector(0, 0, 1), n);
}

TEST(Sphere, WhenNormalOnSphereAtNonAxialPointExpectNormal) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  const double factor = sqrt(3.0) / 3.0;
  auto n = s->normal_at(Point(factor, factor, factor));
  EXPECT_EQ(Vector(factor, factor, factor), n);
}

TEST(Sphere, NormalIsANormalizedVector) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  const double factor = sqrt(3.0) / 3.0;
  auto n = s->normal_at(Point(factor, factor, factor));
  auto normalized = Vector(factor, factor, factor);
  normalized.normalize();
  EXPECT_EQ(normalized, n);
}

TEST(Sphere, ComputingNormalOnTranslatedSphere) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  s->set_transform(Transform::translation(0, 1, 0));
  auto n = s->normal_at(Point(0, 1.70711, -0.70711));
  EXPECT_EQ(Vector(0, 0.70711, -0.70711), n);
}

TEST(Sphere, ComputingNormalOnATransformedSphere) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto m = Transform::scaling(1, 0.5, 1) * Transform::rotation_z(M_PI / 5);
  s->set_transform(m);
  auto x = sqrt(2) / 2;
  auto n = s->normal_at(Point(0, x, -x));
  EXPECT_EQ(Vector(0, 0.97014, -0.24254), n);
}

TEST(Sphere, SphereDefaultMaterial) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Material::MaterialPtr m = s->material();
  EXPECT_EQ(Material::PhongMaterial(), *m);
}

TEST(Sphere, SphereMayBeAssignedAMaterial) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Material::MaterialPtr m = std::make_shared<Material::PhongMaterial>();
  m->set_ambient(1.0);
  s->set_material(m);
  EXPECT_EQ(*m, *(s->material()));
}
