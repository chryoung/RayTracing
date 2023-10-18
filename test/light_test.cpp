#include <gtest/gtest.h>
#include "light/pointlight.h"

using namespace RayTracer;

TEST(Light, CreateAPointLight) {
  Light::PointLight light(Color(1), Point(0, 0, 0));
  EXPECT_EQ(Point(0, 0, 0), light.position());
  EXPECT_EQ(Color(1), light.intensity());
}
