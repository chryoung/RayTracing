#include "utility.h"

#include <gtest/gtest.h>

TEST(Utility, WhenFloatAreEqualExpectComparerReturnTrue) {
  EXPECT_TRUE(RayTracing::is_float_eq(1.0, 1.0));
  EXPECT_TRUE(RayTracing::is_float_eq(1.0, 1));
  EXPECT_TRUE(RayTracing::is_float_eq(1, 1.0));
  EXPECT_TRUE(RayTracing::is_float_eq(1.0L, 1.0));
}

TEST(Utility, WhenTheDifferenceBetweenNumberIsLessThanEpsilonExpectEqual) {
  float a = 1.0 / 3.0;
  float b = a * 3.0;
  EXPECT_TRUE(RayTracing::is_float_eq(1.0, b));
}