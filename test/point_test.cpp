#include "math/_point.h"

#include <gtest/gtest.h>

using namespace RayTracer;

TEST(Point, WhenCreateAPointExpectAPoint) {
  Point p(1, 2, 3);
  EXPECT_TRUE(p.is_point());
  EXPECT_FALSE(p.is_vector());
}

TEST(Point, WhenSetWExpectNoChange) {
  Point p(1, 2, 3);
  p.set_w(10);
  EXPECT_DOUBLE_EQ(Point::POINT_W, p.w());
}

TEST(Point, WhenSetXYWZExpectXYZChangedButW) {
  Point p(1, 2, 3);
  p.set_x(10).set_y(20).set_w(-1).set_z(30);
  EXPECT_DOUBLE_EQ(10, p.x());
  EXPECT_DOUBLE_EQ(20, p.y());
  EXPECT_DOUBLE_EQ(30, p.z());
  EXPECT_DOUBLE_EQ(Point::POINT_W, p.w());
}

TEST(Point, WhenComparePointWithTupleWithW0ExpectEqual) {
  Point p(1, 2, 3);
  Tuple t = Tuple::make_point(1, 2, 3);
  EXPECT_EQ(p, t);
}