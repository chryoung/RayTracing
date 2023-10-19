#include "utility/utility.h"
#include "utility/linked_list.h"
#include "utility/memory_pool.h"

#include <gtest/gtest.h>
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

TEST(LinkedList, NewListIsEmpty) {
  LinkedList<int> a;
  EXPECT_TRUE(a.is_empty());
}

TEST(LinkedList, AddBack) {
  LinkedList<int> a;
  a.add_back(new LinkedListNode<int>(std::make_unique<int>(10)));
  ASSERT_FALSE(a.is_empty());
  LinkedListNode<int>* v = a.pop_front();
  ASSERT_NE(nullptr, v);
  EXPECT_EQ(*(v->val), 10);
}

TEST(MemoryPool, NewMemoryPool) {
  MemoryPool p(2, sizeof(double));
  MemoryPool::Memory m1 = p.alloc();
  MemoryPool::Memory m2 = p.alloc();
  ASSERT_NE(nullptr, m1);
  ASSERT_NE(nullptr, m2);
  ASSERT_NE(nullptr, m1->val->get<double>());
  ASSERT_NE(nullptr, m2->val->get<double>());
  ASSERT_EQ(sizeof(double), (unsigned long long)m2->val->get<double>() - (unsigned long long)m1->val->get<double>());
}
