#include "ray.h"

#include <gtest/gtest.h>

#include "shape/shapebuilder.h"
#include "shape/sphere.h"

using namespace RayTracer;

TEST(Ray, WhenCreateARayExpectARay) {
  Point origin(1, 2, 3);
  Vector direction(4, 5, 6);
  Ray r(origin, direction);
  EXPECT_EQ(origin, r.origin());
  EXPECT_EQ(direction, r.direction());
}

TEST(Ray, WhenGetRayPositionExpectPosition) {
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  EXPECT_EQ(Point(2, 3, 4), r.position(0));
  EXPECT_EQ(Point(3, 3, 4), r.position(1));
  EXPECT_EQ(Point(1, 3, 4), r.position(-1));
  EXPECT_EQ(Point(4.5, 3, 4), r.position(2.5));
}

TEST(Ray, WhenIntersectWithSphereOn2PointsExpect2IntersectPoints) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(4.0, xs[0].time());
  EXPECT_DOUBLE_EQ(6.0, xs[1].time());
}

TEST(Ray, WhenIntersectWithSphereOn1PointExpect1IntersectPoint) {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(5.0, xs[0].time());
  EXPECT_DOUBLE_EQ(5.0, xs[1].time());
}

TEST(Ray, WhenNoIntersectWithSphereExpectNoIntersectPoints) {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(0, xs.size());
}

TEST(Ray, WhenRayOriginIsInSphereExpect2IntersectPoints) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(-1.0, xs[0].time());
  EXPECT_DOUBLE_EQ(1, xs[1].time());
}

TEST(Ray, WhenSphereIsBehindRayOriginExpect2IntersectPoints) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(-6.0, xs[0].time());
  EXPECT_DOUBLE_EQ(-4.0, xs[1].time());
}