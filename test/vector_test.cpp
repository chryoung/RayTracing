#include "math/_vector.h"

#include <gtest/gtest.h>

using namespace RayTracer;

TEST(Vector, WhenCreateAVectorExpectAVector) {
  Vector v(1, 2, 3);
  EXPECT_TRUE(v.is_vector());
  EXPECT_FALSE(v.is_point());
}

TEST(Vector, WhenSetWExpectNoChange) {
  Vector v(1, 2, 3);
  v.set_w(10);
  EXPECT_DOUBLE_EQ(Vector::VECTOR_W, v.w());
}

TEST(Vector, WhenSetXYWZExpectXYZChangedButW) {
  Vector v(1, 2, 3);
  v.set_x(10).set_y(20).set_w(-1).set_z(30);
  EXPECT_DOUBLE_EQ(10, v.x());
  EXPECT_DOUBLE_EQ(20, v.y());
  EXPECT_DOUBLE_EQ(30, v.z());
  EXPECT_DOUBLE_EQ(Vector::VECTOR_W, v.w());
}

TEST(Vector, WhenCompareVectorWithTupleWithW0ExpectEqual) {
  Vector v(1, 2, 3);
  Tuple t = Tuple::make_vector(1, 2, 3);
  EXPECT_EQ(v, t);
}