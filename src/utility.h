#ifndef C271169D_4278_49B6_9E08_01756863FC10
#define C271169D_4278_49B6_9E08_01756863FC10

#include <cmath>

namespace RayTracing {
constexpr float FLOAT_EPSILON = 1e-6;

inline bool is_float_eq(float a, float b) {
  if (abs(a - b) < FLOAT_EPSILON) {
    return true;
  }

  return false;
}
}  // namespace RayTracing

#endif /* C271169D_4278_49B6_9E08_01756863FC10 */
