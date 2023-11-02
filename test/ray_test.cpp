#include "ray/ray.h"

#include <gtest/gtest.h>

#include "geometry/transform.h"
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
  auto xs = s->intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(4.0, xs[0].t());
  EXPECT_DOUBLE_EQ(6.0, xs[1].t());
}

TEST(Ray, WhenIntersectWithSphereOn1PointExpect1IntersectPoint) {
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = s->intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(5.0, xs[0].t());
  EXPECT_DOUBLE_EQ(5.0, xs[1].t());
}

TEST(Ray, WhenNoIntersectWithSphereExpectNoIntersectPoints) {
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = s->intersect(r);
  ASSERT_EQ(0, xs.size());
}

TEST(Ray, WhenRayOriginIsInSphereExpect2IntersectPoints) {
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = s->intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(-1.0, xs[0].t());
  EXPECT_DOUBLE_EQ(1, xs[1].t());
}

TEST(Ray, WhenSphereIsBehindRayOriginExpect2IntersectPoints) {
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = s->intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(-6.0, xs[0].t());
  EXPECT_DOUBLE_EQ(-4.0, xs[1].t());
}

TEST(Ray, WhenTranslateRayExpectNewTranslatedRay) {
  const Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  auto m = Transform::translation(3, 4, 5);
  auto r2 = r.transform(m);
  EXPECT_EQ(r2.origin(), Point(4, 6, 8));
  EXPECT_EQ(r2.direction(), Vector(0, 1, 0));
}

TEST(Ray, WhenScalingRayExpectNewScaledRay) {
  const Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  auto m = Transform::scaling(2, 3, 4);
  auto r2 = r.transform(m);
  EXPECT_EQ(r2.origin(), Point(2, 6, 12));
  EXPECT_EQ(r2.direction(), Vector(0, 3, 0));
}

TEST(Ray, WhenIntersectWithScaledSphereExpectIntersection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  s->set_transform(Transform::scaling(2, 2, 2));
  auto xs = s->intersect(r);
  ASSERT_EQ(2, xs.size());
  EXPECT_DOUBLE_EQ(3, xs[0].t());
  EXPECT_DOUBLE_EQ(7, xs[1].t());
}

TEST(Ray, WhenIntersectWithTranslatedSphereExpectIntersection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  s->set_transform(Transform::translation(5, 0, 0));
  auto xs = s->intersect(r);
  ASSERT_EQ(0, xs.size());
}
