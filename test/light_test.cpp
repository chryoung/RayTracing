#include <gtest/gtest.h>
#include "light/pointlight.h"

using namespace RayTracer;

TEST(Light, CreateAPointLight) {
  Light::PointLight light(Color(1, 1, 1), Point(0, 0, 0));
  EXPECT_EQ(Point(0, 0, 0), light.get_position());
  EXPECT_EQ(Color(1, 1, 1), light.get_intensity());
}
