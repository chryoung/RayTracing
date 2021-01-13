#include "utility/utility.h"

#include <gtest/gtest.h>

using namespace RayTracer;

TEST(Utility, WhenFloatAreEqualExpectComparerReturnTrue) {
  EXPECT_TRUE(is_double_eq(1.0, 1.0));
  EXPECT_TRUE(is_double_eq(1.0, 1));
  EXPECT_TRUE(is_double_eq(1, 1.0));
  EXPECT_TRUE(RayTracer::is_double_eq(1.0L, 1.0));
}

TEST(Utility, WhenTheDifferenceBetweenNumberIsLessThanEpsilonExpectEqual) {
  double a = 1.0 / 3.0;
  double b = a * 3.0;
  EXPECT_TRUE(is_double_eq(1.0, b));
}

TEST(Utility, WhenAIsGreaterThanBExpectTrue) {
  double a = 1.0 / 3.0;
  double b = 0.3;
  EXPECT_TRUE(is_double_gt(a, b));
}

TEST(Utility, WhenAIsGreaterEqualThanBExpectTrue) {
  double a = 1.0 / 3.0;
  double b = 0.3;
  EXPECT_TRUE(is_double_ge(a, b));

  double c = a * 3.0;
  EXPECT_TRUE(is_double_ge(c, 1.0));
}

TEST(Utility, WhenAIsLessThanBExpectTrue) {
  double a = 0.3;
  double b = 1.0 / 3.0;
  EXPECT_TRUE(is_double_lt(a, b));
}

TEST(Utility, WhenAIsLessEqualThanBExpectTrue) {
  double a = 0.3;
  double b = 1.0 / 3.0;
  EXPECT_TRUE(is_double_le(a, b));

  double c = b * 3.0;
  EXPECT_TRUE(is_double_le(1.0, c));
}