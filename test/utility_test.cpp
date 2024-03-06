#include "utility/utility.h"
#include "utility/memory_pool.h"

#include "gtest/gtest.h"
#include <utility>

using namespace RayTracer;

TEST(Utility, WhenFloatAreEqualExpectComparerReturnTrue) {
  EXPECT_TRUE(is_double_eq(1.0, 1.0));
  EXPECT_TRUE(is_double_eq(1.0, 1));
  EXPECT_TRUE(is_double_eq(1, 1.0));
  EXPECT_TRUE(RayTracer::is_double_eq(1.0L, 1.0));
}

TEST(Utility, WhenTheDifferenceBetweenNumberIsLessThanEpsilonExpectEqual) {
  double a = 1.0 / 3.0;
  double b = a * 3.0;
  EXPECT_TRUE(is_double_eq(1.0, b));
}

TEST(Utility, WhenAIsGreaterThanBExpectTrue) {
  double a = 1.0 / 3.0;
  double b = 0.3;
  EXPECT_TRUE(is_double_gt(a, b));
}

TEST(Utility, WhenAIsGreaterEqualThanBExpectTrue) {
  double a = 1.0 / 3.0;
  double b = 0.3;
  EXPECT_TRUE(is_double_ge(a, b));

  double c = a * 3.0;
  EXPECT_TRUE(is_double_ge(c, 1.0));
}

TEST(Utility, WhenAIsLessThanBExpectTrue) {
  double a = 0.3;
  double b = 1.0 / 3.0;
  EXPECT_TRUE(is_double_lt(a, b));
}

TEST(Utility, WhenAIsLessEqualThanBExpectTrue) {
  double a = 0.3;
  double b = 1.0 / 3.0;
  EXPECT_TRUE(is_double_le(a, b));

  double c = b * 3.0;
  EXPECT_TRUE(is_double_le(1.0, c));
}

TEST(MemoryPool, NewMemoryPool) {
  MemoryPool<double> p(2, 1);
  MemoryChunk<double>* m1 = p.alloc();
  MemoryChunk<double>* m2 = p.alloc();
  ASSERT_NE(nullptr, m1);
  ASSERT_NE(nullptr, m2);
  ASSERT_NE(nullptr, m1->get());
  ASSERT_NE(nullptr, m2->get());
  ASSERT_NE(m1->get(), m2->get());
  p.free(m1);
  p.free(m2);
}
