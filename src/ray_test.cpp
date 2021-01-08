#include "ray.h"

#include <gtest/gtest.h>

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