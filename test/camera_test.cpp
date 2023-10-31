#include <gtest/gtest.h>
#include <cmath>
#include "camera/camera.h"
#include "geometry/transform.h"

using namespace RayTracer;

TEST(Camera, ConstructingACamera) {
  int hsize = 160;
  int vsize = 120;
  double field_of_view = M_PI_2;
  Camera camera{hsize, vsize, field_of_view};
  EXPECT_EQ(hsize, camera.hsize());
  EXPECT_EQ(vsize, camera.vsize());
  EXPECT_DOUBLE_EQ(field_of_view, camera.field_of_view());
  EXPECT_EQ(Transform::id(), camera.transform());
}

TEST(Camera, PixelSizeForHorizontalCanvas) {
  Camera c{200, 125, M_PI_2};
  EXPECT_DOUBLE_EQ(0.01, c.pixel_size());
}

TEST(Camera, PixelSizeForVerticalCanvas) {
  Camera c{125, 200, M_PI_2};
  EXPECT_DOUBLE_EQ(0.01, c.pixel_size());
}

TEST(Camera, ConstructingARayThroughCentreOfCanvas) {
  Camera c{201, 101, M_PI_2};
  auto r = c.ray_for_pixel(100, 50);
  EXPECT_EQ(Point(0, 0, 0), r.origin());
  EXPECT_EQ(Vector(0, 0, -1), r.direction());
}

TEST(Camera, ConstructingARayThroughCornerOfCanvas) {
  Camera c{201, 101, M_PI_2};
  auto r = c.ray_for_pixel(0, 0);
  EXPECT_EQ(Point(0, 0, 0), r.origin());
  EXPECT_EQ(Vector(0.66519, 0.33259, -0.66851), r.direction());
}

TEST(Camera, ConstructingARayWhenTheCameraIsTransformed) {
  Camera c{201, 101, M_PI_2};
  c.set_transform(Transform::rotation_y(M_PI_4) * Transform::translation(0, -2, 5));
  auto r = c.ray_for_pixel(100, 50);
  EXPECT_EQ(Point(0, 2, -5), r.origin());
  const double sqrt_2_2 = ::sqrt(2) / 2;
  EXPECT_EQ(Vector(sqrt_2_2, 0, -sqrt_2_2), r.direction());
}
