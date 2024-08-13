#pragma once
#include <cmath>

namespace RayTracer {
constexpr double DOUBLE_EPSILON = 1e-5;

inline bool is_double_eq(double a, double b) {
  return (std::fabs(a - b) < DOUBLE_EPSILON);
}

inline bool is_double_ne(double a, double b) { return !is_double_eq(a, b); }

inline bool is_double_lt(double a, double b) { return a < b; }

inline bool is_double_gt(double a, double b) { return a > b; }

inline bool is_double_le(double a, double b) {
  return (is_double_eq(a, b) || a < b);
}

inline bool is_double_ge(double a, double b) {
  return (is_double_eq(a, b) || a > b);
}
}  // namespace RayTracer

