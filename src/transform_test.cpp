#include "transform.h"

#include <gtest/gtest.h>

#ifdef _MSC_VER
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include "tuple.h"

using namespace RayTracer;

TEST(Transform, WhenTranslatePointExpectTranslatedPoint) {
  auto tf = Transform::translating(5, -3, 2);
  auto p = Tuple::make_point(-3, 4, 5);
  Tuple translated;
  EXPECT_TRUE(tf.multiply_to_tuple(p, translated));
  auto truth = Tuple::make_point(2, 1, 7);
  EXPECT_EQ(truth, translated);
  EXPECT_EQ(truth, tf * p);
}

TEST(Transform, WhenMultiplyByInverseOfATranslationMatrixExpectMoveOpposite) {
  auto tf = Transform::translating(5, -3, 2);
  auto inv = tf.inverse();
  auto p = Tuple::make_point(-3, 4, 5);
  EXPECT_EQ(Tuple::make_point(-8, 7, 3), inv * p);
}

TEST(Transform, WhenTranslateAVectorExpectItself) {
  auto tf = Transform::translating(5, -3, 2);
  auto v = Tuple::make_vector(-3, 4, 5);
  EXPECT_EQ(v, tf * v);
}

TEST(Transform, WhenScaleAVectorExpectAScaledVector) {
  auto tf = Transform::scaling(2, 3, 4);
  auto v = Tuple::make_vector(-4, 6, 8);
  EXPECT_EQ(Tuple::make_vector(-8, 18, 32), tf * v);
}

TEST(Transform, WhenMultiplyByInverseOfAScaleMatrixExpectAScaledVector) {
  auto tf = Transform::scaling(2, 3, 4);
  auto inv = tf.inverse();
  auto v = Tuple::make_vector(-4, 6, 8);
  EXPECT_EQ(Tuple::make_vector(-2, 2, 2), inv * v);
}

TEST(Transform, WhenScaleByANegativeValueExpectReflection) {
  auto tf = Transform::scaling(-1, 1, 1);
  auto p = Tuple::make_point(2, 3, 4);
  EXPECT_EQ(Tuple::make_point(-2, 3, 4), tf * p);
}

TEST(Transform, WhenRotateAPointAroundXAxisExpectRotatedPoint) {
  auto p = Tuple::make_point(0, 1, 0);
  auto half_quarter = Transform::rotation_x(M_PI_4);
  auto full_quarter = Transform::rotation_x(M_PI_2);
  double sqrt_2 = sqrt(2.0);
  EXPECT_EQ(Tuple::make_point(0, sqrt_2 / 2, sqrt_2 / 2), half_quarter * p);
  EXPECT_EQ(Tuple::make_point(0, 0, 1), full_quarter * p);
}

TEST(Transform, WhenRotateAPointUsingInverseMatrixExpectRotateInOppositeDirection) {
  auto p = Tuple::make_point(0, 1, 0);
  auto half_quarter = Transform::rotation_x(M_PI_4);
  auto inv = half_quarter.inverse();
  double sqrt_2 = sqrt(2.0);
  EXPECT_EQ(Tuple::make_point(0, sqrt_2 / 2, -sqrt_2 / 2), inv * p);
}

TEST(Transform, WhenRotateAPointAroundYAxisExpectRotatedPoint) {
  auto p = Tuple::make_point(0, 0, 1);
  auto half_quarter = Transform::rotation_y(M_PI_4);
  auto full_quarter = Transform::rotation_y(M_PI_2);
  double sqrt_2 = sqrt(2.0);
  EXPECT_EQ(Tuple::make_point(sqrt_2 / 2, 0, sqrt_2 / 2), half_quarter * p);
  EXPECT_EQ(Tuple::make_point(1, 0, 0), full_quarter * p);
}

TEST(Transform, WhenRotateAPointAroundZAxisExpectRotatedPoint) {
  auto p = Tuple::make_point(0, 1, 0);
  auto half_quarter = Transform::rotation_z(M_PI_4);
  auto full_quarter = Transform::rotation_z(M_PI_2);
  double sqrt_2 = sqrt(2.0);
  EXPECT_EQ(Tuple::make_point(-sqrt_2 / 2, sqrt_2 / 2, 0), half_quarter * p);
  EXPECT_EQ(Tuple::make_point(-1, 0, 0), full_quarter * p);
}

TEST(Transform, WhenShearingAPointExpectShearedPoint) {
  auto tf = Transform::shearing(1, 0, 0, 0, 0, 0);
  auto p = Tuple::make_point(2, 3, 4);
  EXPECT_EQ(Tuple::make_point(5, 3, 4), tf * p);

  tf = Transform::shearing(0, 1, 0, 0, 0, 0);
  EXPECT_EQ(Tuple::make_point(6, 3, 4), tf * p);

  tf = Transform::shearing(0, 0, 1, 0, 0, 0);
  EXPECT_EQ(Tuple::make_point(2, 5, 4), tf * p);

  tf = Transform::shearing(0, 0, 0, 1, 0, 0);
  EXPECT_EQ(Tuple::make_point(2, 7, 4), tf * p);

  tf = Transform::shearing(0, 0, 0, 0, 1, 0);
  EXPECT_EQ(Tuple::make_point(2, 3, 6), tf * p);

  tf = Transform::shearing(0, 0, 0, 0, 0, 1);
  EXPECT_EQ(Tuple::make_point(2, 3, 7), tf * p);
}

TEST(Transform, WhenChainingTransformationExpectFinalTransformedPoint) {
  auto p = Tuple::make_point(1, 0, 1);
  auto a = Transform::rotation_x(M_PI_2);
  auto b = Transform::scaling(5, 5, 5);
  auto c = Transform::translating(10, 5, 7);

  auto p2 = a * p;
  EXPECT_EQ(Tuple::make_point(1, -1, 0), p2);

  auto p3 = b * p2;
  EXPECT_EQ(Tuple::make_point(5, -5, 0), p3);

  auto p4 = c * p3;
  EXPECT_EQ(Tuple::make_point(15, 0, 7), p4);

  auto t = c * b * a;
  EXPECT_EQ(Tuple::make_point(15, 0, 7), t * p);
}

TEST(Transform, WhenUseTransformationBuilderToBuildChainingTransformationExpectCorrectTransformation) {
  Transform::TransformationBuilder t;
  t.rotate_x(M_PI_2).scale(5, 5, 5).translate(10, 5, 7);
  auto p = Tuple::make_point(1, 0, 1);
  EXPECT_EQ(Tuple::make_point(15, 0, 7), t.build() * p);
}