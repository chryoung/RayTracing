#include <gtest/gtest.h>
#include "math/tuple.h"
#include "image/color.h"
#include "material/stripe_pattern.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "geometry/transform.h"

using namespace RayTracer;

TEST(Pattern, CreatingAStripPattern) {
  Material::StripePattern pattern;
  EXPECT_EQ(Color::make_white(), pattern.a());
  EXPECT_EQ(Color::make_black(), pattern.b());
}

TEST(Pattern, AStripePatternIsConstantInY) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 1, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 2, 0)));
}

TEST(Pattern, AStripePatternIsConstantInZ) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 1)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 2)));
}

TEST(Pattern, AStripePatternAlternatesInX) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  Color black = Color::make_black();
  EXPECT_EQ(white, pattern.stripe_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(0.9, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(1, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(-0.1, 0, 0)));
  EXPECT_EQ(black, pattern.stripe_at(Point(-1, 0, 0)));
  EXPECT_EQ(white, pattern.stripe_at(Point(-1.1, 0, 0)));
}

TEST(Pattern, StripesWithAnObjectTransformation) {
  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  object->set_transform(Transform::scaling(2, 2, 2));
  Material::StripePattern pattern;
  Color c = pattern.stripe_at_object(object, Point(1.5, 0, 0));
  EXPECT_EQ(Color::make_white(), c);
}

TEST(Pattern, StripesWithBothAnObjectAndAPatternTransformation) {
  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  object->set_transform(Transform::scaling(2, 2, 2));
  Material::StripePattern pattern;
  pattern.set_transform(Transform::translation(0.5, 0, 0));
  Color c = pattern.stripe_at_object(object, Point{2.5, 0, 0});
  EXPECT_EQ(Color::make_white(), c);
}
