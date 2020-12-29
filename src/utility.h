#include <cmath>

namespace RayTracing {
  constexpr float FLOAT_EPSILON = 1e-6;

  inline bool is_float_eq(float a, float b) {
    if (abs(a - b) < FLOAT_EPSILON) {
      return true;
    }

    return false;
  }
} // namespace RayTracing
