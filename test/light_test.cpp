#include <gtest/gtest.h>
#include "light/pointlight.h"

using namespace RayTracer;

TEST(Light, CreateAPointLight) {
  Light::PointLight light(Point(0, 0, 0), Color(1));
  EXPECT_EQ(Point(0, 0, 0), light.position());
  EXPECT_EQ(Color(1), light.intensity());
}
