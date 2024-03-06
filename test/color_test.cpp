#include "image/color.h"

#include "gtest/gtest.h"

using namespace RayTracer;

TEST(Color, WhenCreateColorExpectANewColor) {
  Color c(-0.5, 0.4, 1.7);
  EXPECT_DOUBLE_EQ(-0.5, c.red());
  EXPECT_DOUBLE_EQ(0.4, c.green());
  EXPECT_DOUBLE_EQ(1.7, c.blue());
}

TEST(Color, WhenAddColorsExpectNewColor) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  EXPECT_EQ(Color(1.6, 0.7, 1.0), c1 + c2);
}

TEST(Color, WhenSubstractColorsExpectNewColor) {
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);

  EXPECT_EQ(Color(0.2, 0.5, 0.5), c1 - c2);
}

TEST(Color, WhenMultiplyAColorByAScalarExpectNewColor) {
  Color c(0.2, 0.3, 0.4);
  EXPECT_EQ(Color(0.4, 0.6, 0.8), c * 2);
}

TEST(Color, WhenMultiplyAColorByAColorExpectNewColor) {
  Color c1(1, 0.2, 0.4);
  Color c2(0.9, 1, 0.1);
  EXPECT_EQ(Color(0.9, 0.2, 0.04), c1 * c2);
}
