#include "shape/plane.h"
#include "shape/shapebuilder.h"
#include "ray/ray.h"

#include <gtest/gtest.h>

using namespace RayTracer;

TEST(Plane, NormalOfPlaneIsConstantEveryWhere) {
  auto plane = Shape::ShapeBuilder::build<Shape::Plane>();
  EXPECT_EQ(Vector(0, 1, 0), plane->local_normal_at(Point{0, 0, 0}));
  EXPECT_EQ(Vector(0, 1, 0), plane->local_normal_at(Point{10, 0, -10}));
  EXPECT_EQ(Vector(0, 1, 0), plane->local_normal_at(Point{-5, 0, 150}));
}

TEST(Plane, IntersectWithARayParallelToPlane) {
  auto plane = Shape::ShapeBuilder::build<Shape::Plane>();
  Ray r{0, 10, 0, 0, 0, 1};
  auto xs = plane->local_intersect(r);
  EXPECT_TRUE(xs.empty());
}

TEST(Plane, IntersectWithACoplanarRay) {
  auto plane = Shape::ShapeBuilder::build<Shape::Plane>();
  Ray r{0, 0, 0, 0, 0, 1};
  auto xs = plane->local_intersect(r);
  EXPECT_TRUE(xs.empty());
}

TEST(Plane, ARayIntersectingAPlaneFromAbove) {
  auto plane = Shape::ShapeBuilder::build<Shape::Plane>();
  Ray r{0, 1, 0, 0, -1, 0};
  auto xs = plane->local_intersect(r);
  ASSERT_EQ(1, xs.size());
  EXPECT_DOUBLE_EQ(1.0, xs[0].t());
  EXPECT_EQ(plane, xs[0].object());
}

TEST(Plane, ARayIntersectingAPlaneFromBelow) {
  auto plane = Shape::ShapeBuilder::build<Shape::Plane>();
  Ray r{0, -1, 0, 0, 1, 0};
  auto xs = plane->local_intersect(r);
  ASSERT_EQ(1, xs.size());
  EXPECT_DOUBLE_EQ(1.0, xs[0].t());
  EXPECT_EQ(plane, xs[0].object());
}
