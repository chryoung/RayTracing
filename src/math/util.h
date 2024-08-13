#pragma once
#include "tuple.h"

namespace RayTracer {

inline Vector reflect(const Vector& in, const Vector& normal) {
  return in - normal * 2 * in.dot(normal);
}

}

