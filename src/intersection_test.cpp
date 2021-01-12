#include "intersection.h"
#include "intersection_collection.h"
#include "shape/sphere.h"
#include "shape/shapebuilder.h"
#include "ray.h"
#include "tuple.h"

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