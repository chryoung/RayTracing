#include "math/tuple.h"

#include <gtest/gtest.h>

#include <cmath>

using RayTracer::Tuple;

TEST(Tuple, WhenTupleIsPointExpectWEqualsOne) {
  Tuple a(4.3, -4.2, 3.1, 1.0);
  EXPECT_DOUBLE_EQ(4.3, a.x());
  EXPECT_DOUBLE_EQ(-4.2, a.y());
  EXPECT_DOUBLE_EQ(3.1, a.z());
  EXPECT_DOUBLE_EQ(1.0, a.w());
  EXPECT_TRUE(a.is_point());
  EXPECT_FALSE(a.is_vector());
}

TEST(Tuple, WhenTupleIsVectorExpectWEqualsZero) {
  Tuple a(4.3, -4.2, 3.1, 0.0);
  EXPECT_DOUBLE_EQ(4.3, a.x());
  EXPECT_DOUBLE_EQ(-4.2, a.y());
  EXPECT_DOUBLE_EQ(3.1, a.z());
  EXPECT_DOUBLE_EQ(0.0, a.w());
  EXPECT_FALSE(a.is_point());
  EXPECT_TRUE(a.is_vector());
}

TEST(Tuple, WhenMakePointExpectANewPoint) {
  Tuple a = Tuple::make_point(4, -4, 3);
  EXPECT_DOUBLE_EQ(4.0, a.x());
  EXPECT_DOUBLE_EQ(-4.0, a.y());
  EXPECT_DOUBLE_EQ(3.0, a.z());
  EXPECT_DOUBLE_EQ(1.0, a.w());
}

TEST(Tuple, WhenMakeVectorExpectANewVector) {
  Tuple a = Tuple::make_vector(4, -4, 3);
  EXPECT_DOUBLE_EQ(4.0, a.x());
  EXPECT_DOUBLE_EQ(-4.0, a.y());
  EXPECT_DOUBLE_EQ(3.0, a.z());
  EXPECT_DOUBLE_EQ(0.0, a.w());
}

TEST(Tuple, WhenTuplesAreEqualExpectComparerReturnTrue) {
  Tuple a = Tuple::make_vector(1.0, 1.0, 3.14);
  Tuple b = Tuple::make_vector(1.0, 1.0, 3.14);
  EXPECT_TRUE(a == b);
  EXPECT_EQ(a, b);

  Tuple c = Tuple::make_point(1.0, 1.0, 3.14);
  Tuple d = Tuple::make_point(1.0, 1.0, 3.14);
  EXPECT_TRUE(c == d);
  EXPECT_EQ(c, d);
}

TEST(Tuple, WhenAddPointAndVectorExpectPoint) {
  Tuple a(3, -2, 5, 1);
  Tuple b(-2, 3, 1, 0);
  Tuple c = a + b;
  Tuple d(a);
  d += b;
  Tuple truth(1, 1, 6, 1);
  EXPECT_EQ(truth, c);
  EXPECT_EQ(truth, d);
}

TEST(Tuple, WhenSubstractTwoPointsExpectVector) {
  Tuple p1 = Tuple::make_point(3, 2, 1);
  Tuple p2 = Tuple::make_point(5, 6, 7);
  Tuple p3 = p1 - p2;
  Tuple p4(p1);
  p4 -= p2;
  Tuple truth = Tuple::make_vector(-2, -4, -6);
  EXPECT_EQ(truth, p3);
  EXPECT_EQ(truth, p4);
}

TEST(Tuple, WhenSubstractAVectorFromAPointExpectAPoint) {
  Tuple p1 = Tuple::make_point(3, 2, 1);
  Tuple v = Tuple::make_vector(5, 6, 7);
  Tuple truth = Tuple::make_point(-2, -4, -6);
  Tuple diff = p1 - v;
  Tuple p2(p1);
  p2 -= v;
  EXPECT_EQ(truth, diff);
  EXPECT_EQ(truth, p2);
}

TEST(Tuple, WhenSubstractTwoVectorsExpectAVector) {
  Tuple v1 = Tuple::make_vector(3, 2, 1);
  Tuple v2 = Tuple::make_vector(5, 6, 7);
  Tuple diff = v1 - v2;
  Tuple truth = Tuple::make_vector(-2, -4, -6);
  EXPECT_EQ(truth, diff);
}

TEST(Tuple, WhenSubstractAVectorFromZeroVectorExpectNegating) {
  Tuple zero = Tuple::make_vector(0, 0, 0);
  Tuple v = Tuple::make_vector(1, -2, 3);
  auto diff = zero - v;
  auto truth = Tuple::make_vector(-1, 2, -3);
  EXPECT_EQ(truth, diff);
}

TEST(Tuple, WhenNegateAVectorExpectNegating) {
  Tuple a(1, -2, 3, -4);
  EXPECT_EQ(Tuple(-1, 2, -3, 4), -a);
}

TEST(Tuple, WhenMultiplyATupleByAScalarExpectTuple) {
  Tuple a(1, -2, 3, -4);
  EXPECT_EQ(Tuple(3.5, -7, 10.5, -14), a * 3.5);
}

TEST(Tuple, WhenMultiplyATupleByAFractionExpectTuple) {
  Tuple a(1, -2, 3, -4);
  EXPECT_EQ(Tuple(0.5, -1, 1.5, -2), a * 0.5);
}

TEST(Tuple, WhenDividingATupleByAScalarExpectTuple) {
  Tuple a(1, -2, 3, -4);
  EXPECT_EQ(Tuple(0.5, -1, 1.5, -2), a / 2);
}

TEST(Tuple, WhenGetMagnitudeFromVectorWithAxisEqualsOneExpectUnitLength) {
  Tuple v1 = Tuple::make_vector(1, 0, 0);
  EXPECT_DOUBLE_EQ(1.0, v1.magnitude());

  Tuple v2 = Tuple::make_vector(0, 1, 0);
  EXPECT_DOUBLE_EQ(1.0, v2.magnitude());

  Tuple v3 = Tuple::make_vector(0, 0, 1);
  EXPECT_DOUBLE_EQ(1.0, v3.magnitude());
}

TEST(Tuple, WhenGetMagnitudeFromAnyVectorExpectCorrectValue) {
  Tuple v1 = Tuple::make_vector(1, 2, 3);
  EXPECT_DOUBLE_EQ(std::sqrt(14), v1.magnitude());

  Tuple v2 = Tuple::make_vector(-1, -2, -3);
  EXPECT_DOUBLE_EQ(std::sqrt(14), v2.magnitude());
}

TEST(Tuple, WhenNormalizeAVectorExpectANormalizedVector) {
  Tuple v1 = Tuple::make_vector(4, 0, 0);
  v1.normalize();
  EXPECT_EQ(Tuple::make_vector(1, 0, 0), v1);

  Tuple v2 = Tuple::make_vector(1, 2, 3);
  v2.normalize();
  EXPECT_EQ(Tuple::make_vector(0.26726124, 0.53452248, 0.80178372), v2);
}

TEST(Tuple, WhenGetMagnitudeFromANormalizedVectorExpectOne) {
  Tuple v = Tuple::make_vector(1, 2, 3);
  v.normalize();
  EXPECT_DOUBLE_EQ(1.0, v.magnitude());
}

TEST(Tuple, WhenGetDotOfTwoVectorsExpectACorrectScalar) {
  Tuple v1 = Tuple::make_vector(1, 2, 3);
  Tuple v2 = Tuple::make_vector(2, 3, 4);
  EXPECT_DOUBLE_EQ(20.0, v1.dot(v2));
  EXPECT_DOUBLE_EQ(20.0, v2.dot(v1));
}

TEST(Tuple, WhenGetCrossOfTwoVectorsExpectAPerpendicularVector) {
  Tuple v1 = Tuple::make_vector(1, 2, 3);
  Tuple v2 = Tuple::make_vector(2, 3, 4);
  EXPECT_EQ(Tuple::make_vector(-1, 2, -1), v1.cross(v2));
  EXPECT_EQ(Tuple::make_vector(1, -2, 1), v2.cross(v1));
}