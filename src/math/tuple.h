#pragma once
#include "_point.h"
#include "_tuple.h"
#include "_vector.h"
#include "utility/utility.h"

namespace RayTracer {

inline Tuple operator+(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w());
}

inline Tuple operator-(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w());
}

inline Tuple operator*(const Tuple& a, double b) { return Tuple(a.x() * b, a.y() * b, a.z() * b, a.w() * b); }

inline Tuple operator/(const Tuple& a, double b) { return Tuple(a.x() / b, a.y() / b, a.z() / b, a.w() / b); }

inline Vector operator*(const Vector& a, double b) { return Vector(a.x() * b, a.y() * b, a.z() * b); }

inline Vector operator/(const Vector& a, double b) { return Vector(a.x() / b, a.y() / b, a.z() / b); }

inline Point operator*(const Point& a, double b) { return Point(a.x() * b, a.y() * b, a.z() * b); }

inline Point operator/(const Point& a, double b) { return Point(a.x() / b, a.y() / b, a.z() / b); }

inline Point operator+(const Vector& a, const Point& b) { return Point(a.x() + b.x(), a.y() + b.y(), a.z() + b.z()); }

inline Point operator-(const Vector& a, const Point& b) { return Point(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); }

inline Point operator+(const Point& a, const Vector& b) { return Point(a.x() + b.x(), a.y() + b.y(), a.z() + b.z()); }

inline Point operator-(const Point& a, const Vector& b) { return Point(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); }

inline Vector operator-(const Point& a, const Point& b) { return Vector(a.x() - b.x(), a.y() - b.y(), a.z() - b.z()); }

inline Vector operator+(const Vector& a, const Vector& b) {
  return Vector(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

inline Vector operator-(const Vector& a, const Vector& b) {
  return Vector(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

}  // namespace RayTracer

