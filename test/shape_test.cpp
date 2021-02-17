#include "shape/sphere.h"

#include <gtest/gtest.h>

#include "shape/shapebuilder.h"
#include "geometry/transform.h"
#include "math/matrix.h"

using namespace RayTracer;

TEST(Sphere, WhenCreateSphereExpectHasIdTransformation) {
  auto id = Matrix::id(Transform::TRANSFORMATION_MATRIX_ROWS);
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  EXPECT_EQ(id, s->transform());
}

TEST(Sphere, WhenSetTransformExpectTransform) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto t = Transform::translating(2,3,4);
  s->set_transform(t);
  EXPECT_EQ(t, s->transform());
}
