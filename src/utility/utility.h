#ifndef C271169D_4278_49B6_9E08_01756863FC10
#define C271169D_4278_49B6_9E08_01756863FC10

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

#endif /* C271169D_4278_49B6_9E08_01756863FC10 */
