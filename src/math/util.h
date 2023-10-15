#ifndef ADDFE29F_F138_4E69_A173_22DE5C28C563
#define ADDFE29F_F138_4E69_A173_22DE5C28C563

#include "tuple.h"

namespace RayTracer {

inline Vector reflect(const Vector& in, const Vector& normal) {
  return in - normal * 2 * in.dot(normal);
}

}

#endif
