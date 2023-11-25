#include <gtest/gtest.h>
#include "math/tuple.h"
#include "image/color.h"
#include "material/stripe_pattern.h"

using namespace RayTracer;

TEST(Pattern, CreatingAStripPattern) {
  StripePattern pattern;
  EXPECT_EQ(Color::make_white(), pattern.a());
  EXPECT_EQ(Color::make_black(), pattern.b());
}

TEST(Pattern, AStripePatternIsConstantInY) {
  StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 1, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 2, 0)));
}

TEST(Pattern, AStripePatternIsConstantInZ) {
  StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 1)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 2)));
}

TEST(Pattern, AStripePatternAlternatesInX) {
  StripePattern pattern;
  Color white = Color::make_white();
  Color black = Color::make_black();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0.9, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(1, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(-0.1, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(-1, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(-1.1, 0, 0)));
}
