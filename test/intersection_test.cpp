#include "ray/intersection.h"
#include "ray/intersection_collection.h"
#include "shape/sphere.h"
#include "shape/shapebuilder.h"
#include "ray/ray.h"

#include <gtest/gtest.h>

using namespace RayTracer;

TEST(Intersection, WhenCreateIntersectionExpectIntersection) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i(3.5, s);
  EXPECT_EQ(3.5, i.time());
  EXPECT_EQ(s, i.object());
}

TEST(Intersection, WhenAggregatingIntersectionsExpectIntersectionCollection) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(1, s);
  Intersection i2(2, s);
  IntersectionCollection xs{i1, i2};
  ASSERT_EQ(2, xs.size());
  EXPECT_EQ(1, xs[0].time());
  EXPECT_EQ(2, xs[1].time());
}

TEST(Intersection, WhenGetIntersectionsFromRayExpectIntersectionCollection) {
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  auto xs = r.intersect(s);
  ASSERT_EQ(2, xs.size());
  EXPECT_EQ(s, xs[0].object());
  EXPECT_EQ(s, xs[1].object());
}

TEST(Intersection, WhenHitIntersectionWithAllPositiveTExpectPositiveT) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(1, s);
  Intersection i2(2, s);
  IntersectionCollection xs{i2, i1};
  auto hit = xs.hit();
  ASSERT_TRUE(hit.has_value());
  EXPECT_EQ(i1, *hit);
}

TEST(Intersection, WhenHitIntersectionWithOneNegativeTExpectPositiveT) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(-1, s);
  Intersection i2(1, s);
  IntersectionCollection xs{i2, i1};
  auto hit = xs.hit();
  ASSERT_TRUE(hit.has_value());
  EXPECT_EQ(i2, *hit);
}

TEST(Intersection, WhenHitIntersectionWithAllNegativeTExpectNullOpt) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(-2, s);
  Intersection i2(-1, s);
  IntersectionCollection xs{i2, i1};
  EXPECT_EQ(std::nullopt, xs.hit());
}

TEST(Intersection, WhenHitIntersectionWithManyTExpectLowestPositiveT) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(5, s);
  Intersection i2(7, s);
  Intersection i3(-3, s);
  Intersection i4(2, s);
  IntersectionCollection xs{i1, i2, i3, i4};
  auto hit = xs.hit();
  ASSERT_TRUE(hit.has_value());
  EXPECT_EQ(i4, *hit);
}

TEST(Intersection, WhenInsertLowestTToIntersectionsExpectLowestPositiveT) {
  auto s = Shape::ShapeBuilder::build<Shape::Sphere>();
  Intersection i1(5, s);
  Intersection i2(7, s);
  Intersection i3(-3, s);
  Intersection i4(2, s);
  Intersection i5(1, s);
  IntersectionCollection xs{i1, i2, i3, i4};
  xs.insert(i5);
  auto hit = xs.hit();
  ASSERT_TRUE(hit.has_value());
  EXPECT_EQ(i5, *hit);
}