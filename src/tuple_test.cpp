#include <gtest/gtest.h>
#include "tuple.h"

using RayTracing::Tuple;

TEST(Tuple, WhenTupleIsPointExpectWEqualsOne) {
  Tuple* a = Tuple::make_tuple(4.3, -4.2, 3.1, 1.0);
  ASSERT_FLOAT_EQ(4.3, a->x());
  ASSERT_FLOAT_EQ(-4.2, a->y());
  ASSERT_FLOAT_EQ(3.1, a->z());
  ASSERT_FLOAT_EQ(1.0, a->w());
  ASSERT_TRUE(a->is_point());
  ASSERT_FALSE(a->is_vector());
  delete a;
}

TEST(Tuple, WhenTupleIsVectorExpectWEqualsZero) {
  Tuple* a = Tuple::make_tuple(4.3, -4.2, 3.1, 0.0);
  ASSERT_FLOAT_EQ(4.3, a->x());
  ASSERT_FLOAT_EQ(-4.2, a->y());
  ASSERT_FLOAT_EQ(3.1, a->z());
  ASSERT_FLOAT_EQ(0.0, a->w());
  ASSERT_FALSE(a->is_point());
  ASSERT_TRUE(a->is_vector());
  delete a;
}

TEST(Tuple, WhenMakePointExpectANewPoint) {
  Tuple* a = Tuple::make_point(4, -4, 3);
  ASSERT_FLOAT_EQ(4.0, a->x());
  ASSERT_FLOAT_EQ(-4.0, a->y());
  ASSERT_FLOAT_EQ(3.0, a->z());
  ASSERT_FLOAT_EQ(1.0, a->w());
  delete a;
}

TEST(Tuple, WhenMakeVectorExpectANewVector) {
  Tuple* a = Tuple::make_vector(4, -4, 3);
  ASSERT_FLOAT_EQ(4.0, a->x());
  ASSERT_FLOAT_EQ(-4.0, a->y());
  ASSERT_FLOAT_EQ(3.0, a->z());
  ASSERT_FLOAT_EQ(0.0, a->w());
  delete a;
}