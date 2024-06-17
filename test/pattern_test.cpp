#include <gtest/gtest.h>
#include "material/pattern.h"
#include "math/tuple.h"
#include "image/color.h"
#include "material/stripe_pattern.h"
#include "shape/shapebuilder.h"
#include "shape/sphere.h"
#include "geometry/transform.h"

using namespace RayTracer;

class TestPattern : public Material::Pattern {
 public:
  Color pattern_at(const Point& p) override {
    return Color(p.x(), p.y(), p.z());
  }
};

TEST(Pattern, CreatingAStripPattern) {
  Material::StripePattern pattern;
  EXPECT_EQ(Color::make_white(), pattern.a());
  EXPECT_EQ(Color::make_black(), pattern.b());
}

TEST(Pattern, AStripePatternIsConstantInY) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 1, 0)));
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 2, 0)));
}

TEST(Pattern, AStripePatternIsConstantInZ) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 0, 1)));
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 0, 2)));
}

TEST(Pattern, AStripePatternAlternatesInX) {
  Material::StripePattern pattern;
  Color white = Color::make_white();
  Color black = Color::make_black();
  EXPECT_EQ(white, pattern.pattern_at(Point(0, 0, 0)));
  EXPECT_EQ(white, pattern.pattern_at(Point(0.9, 0, 0)));
  EXPECT_EQ(black, pattern.pattern_at(Point(1, 0, 0)));
  EXPECT_EQ(black, pattern.pattern_at(Point(-0.1, 0, 0)));
  EXPECT_EQ(black, pattern.pattern_at(Point(-1, 0, 0)));
  EXPECT_EQ(white, pattern.pattern_at(Point(-1.1, 0, 0)));
}

TEST(Pattern, StripesWithAnObjectTransformation) {
  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  object->set_transform(Transform::scaling(2, 2, 2));
  Material::StripePattern pattern;
  Color c = pattern.pattern_at_shape(object, Point(1.5, 0, 0));
  EXPECT_EQ(Color::make_white(), c);
}

TEST(Pattern, StripesWithBothAnObjectAndAPatternTransformation) {
  Shape::BasicShapePtr object = Shape::ShapeBuilder::build<Shape::Sphere>();
  object->set_transform(Transform::scaling(2, 2, 2));
  Material::StripePattern pattern;
  pattern.set_transform(Transform::translation(0.5, 0, 0));
  Color c = pattern.pattern_at_shape(object, Point{2.5, 0, 0});
  EXPECT_EQ(Color::make_white(), c);
}

TEST(Pattern, DefaultPatternTransformation) {
  TestPattern pattern;
  EXPECT_EQ(Transform::id(), pattern.transform());
}

TEST(Pattern, AssignTransform) {
  TestPattern pattern;
  pattern.set_transform(Transform::translation(1, 2, 3));
  EXPECT_EQ(Transform::translation(1, 2, 3), pattern.transform());
}

TEST(Pattern, PatternWithObjectTransformation) {
  auto shape = Shape::ShapeBuilder::build<Shape::Sphere>();
  shape->set_transform(Transform::scaling(2, 2, 2));
  TestPattern pattern;
  auto c = pattern.pattern_at_shape(shape, Point(2, 3, 4));
  EXPECT_EQ(Color(1, 1.5, 2), c);
}

TEST(Pattern, PatternWithPatternTransformation) {
  auto shape = Shape::ShapeBuilder::build<Shape::Sphere>();
  TestPattern pattern;
  pattern.set_transform(Transform::scaling(2, 2, 2));
  auto c = pattern.pattern_at_shape(shape, Point(2, 3, 4));
  EXPECT_EQ(Color(1, 1.5, 2), c);
}

TEST(Pattern, PatternWithObjectTransformationPatternTransformation) {
  auto shape = Shape::ShapeBuilder::build<Shape::Sphere>();
  shape->set_transform(Transform::scaling(2, 2, 2));
  TestPattern pattern;
  pattern.set_transform(Transform::translation(0.5, 1, 1.5));
  auto c = pattern.pattern_at_shape(shape, Point(2.5, 3, 3.5));
  EXPECT_EQ(Color(0.75, 0.5, 0.25), c);
}