#include "material/material.h"
#include "shape/basicshape.h"

#include <cmath>
#include <memory>
#include "gtest/gtest.h"

#include "shape/shapebuilder.h"
#include "geometry/transform.h"
#include "math/matrix.h"
#include "math/tuple.h"
#include "material/phong.h"
#include "ray/ray.h"
#include "ray/intersection_collection.h"

using namespace RayTracer;

class TestShape : public Shape::BasicShape {
 public:
   TestShape(std::uint64_t id): Shape::BasicShape{id}, saved_ray{Ray{0, 0, 0, 0, 0, 0}} {}
   ~TestShape() = default;
   Ray saved_ray;
 protected:
  Vector local_normal_at(const Point& local_point) override {
    return Vector{local_point.x(), local_point.y(), local_point.z()};
  }

  IntersectionCollection local_intersect(const Ray& local_test_ray) override {
    saved_ray = local_test_ray;

    return IntersectionCollection{};
  }
};


TEST(Shape, DefaultTransformation) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  EXPECT_EQ(Transform::id(), s->transform());
}

TEST(Shape, AssignTransformation) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  auto t = Transform::translation(2, 3, 4);
  s->set_transform(t);
  EXPECT_EQ(t, s->transform());
}

TEST(Shape, DefaultMaterial) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  EXPECT_EQ(Material::PhongMaterial(), *s->material());
}

TEST(Shape, AssignMaterial) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  Material::PhongMaterial m;
  m.set_ambient(1);
  s->set_material(std::make_shared<Material::PhongMaterial>(m));
  EXPECT_EQ(m, *s->material());
}

TEST(Shape, IntersectScaledShapeWithRay) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  s->set_transform(Transform::scaling(2, 2, 2));
  auto xs = s->intersect(r);
  EXPECT_EQ(Point(0, 0, -2.5), s->saved_ray.origin());
  EXPECT_EQ(Vector(0, 0, 0.5), s->saved_ray.direction());
}

TEST(Shape, IntersectTranslatedShapeWithRay) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  Ray r{Point{0, 0, -5}, Vector{0, 0, 1}};
  s->set_transform(Transform::translation(5, 0, 0));
  auto xs = s->intersect(r);
  EXPECT_EQ(Point(-5, 0, -5), s->saved_ray.origin());
  EXPECT_EQ(Vector(0, 0, 1), s->saved_ray.direction());
}

TEST(Shape, ComputeNormalOnTraslatedShape) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  s->set_transform(Transform::translation(0, 1, 0));
  auto n = s->normal_at(Point{0, 1.70711, -0.70711});

  EXPECT_EQ(Vector(0, 0.70711, -0.70711), n);
}

TEST(Shape, ComputeNormalOnTransformedShape) {
  auto s = Shape::ShapeBuilder::build<TestShape>();
  s->set_transform(Transform::scaling(1, 0.5, 1) * Transform::rotation_z(M_PI / 5.0));
  const double sqrt_2 = std::sqrt(2) / 2.0;
  auto n = s->normal_at(Point{0, sqrt_2, -sqrt_2});

  EXPECT_EQ(Vector(0, 0.97014, -0.24254), n);
}
