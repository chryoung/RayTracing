#ifndef C9E0998C_94E3_4D8B_B8FC_1C74D8637378
#define C9E0998C_94E3_4D8B_B8FC_1C74D8637378

#include <cmath>
#include <ostream>
#include <utility>

#include "utility.h"

namespace RayTracer {
class Tuple {
 public:
  static constexpr int TUPLE_DIMENSIONS = 4;
  Tuple(double x, double y, double z, double w) : _x(x), _y(y), _z(z), _w(w) {}
  Tuple() : Tuple(0, 0, 0, 0) {}

  static constexpr double POINT_W = 1.0;
  static constexpr double VECTOR_W = 0.0;

  static Tuple make_point(double x, double y, double z) { return Tuple(x, y, z, POINT_W); }

  static Tuple make_vector(double x, double y, double z) { return Tuple(x, y, z, VECTOR_W); }

  double x() { return _x; }
  double y() { return _y; }
  double z() { return _z; }
  double w() { return _w; }

  double x() const { return _x; }
  double y() const { return _y; }
  double z() const { return _z; }
  double w() const { return _w; }

  Tuple& set_x(double x) {
    _x = x;

    return *this;
  }

  Tuple& set_y(double y) {
    _y = y;

    return *this;
  }

  Tuple& set_z(double z) {
    _z = z;

    return *this;
  }

  Tuple& set_w(double w) {
    _w = w;

    return *this;
  }

  double magnitude() { return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w); }

  double magnitude() const { return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w); }

  void normalize() {
    double m = magnitude();
    _x = _x / m;
    _y = _y / m;
    _z = _z / m;
    _w = _w / m;
  }

  bool is_point() { return is_double_eq(_w, POINT_W); }
  bool is_point() const { return is_double_eq(_w, POINT_W); }

  bool is_vector() { return is_double_eq(_w, VECTOR_W); }
  bool is_vector() const { return is_double_eq(_w, VECTOR_W); }

  Tuple& operator+=(const Tuple& other) {
    set_x(_x + other._x);
    set_y(_y + other._y);
    set_z(_z + other._z);
    set_w(_w + other._w);

    return *this;
  }

  Tuple& operator-=(const Tuple& other) {
    set_x(_x - other._x);
    set_y(_y - other._y);
    set_z(_z - other._z);
    set_w(_w - other._w);

    return *this;
  }

  Tuple operator-() const { return Tuple(-_x, -_y, -_z, -_w); }

  double dot(const Tuple& other) { return _x * other._x + _y * other._y + _z * other._z + _w * other._w; }

  Tuple cross(const Tuple& other) {
    return make_vector(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
  }

 private:
  double _x;
  double _y;
  double _z;
  double _w;
};

inline bool operator==(const Tuple& a, const Tuple& b) {
  return is_double_eq(a.w(), b.w()) && is_double_eq(a.x(), b.x()) && is_double_eq(a.y(), b.y()) &&
         is_double_eq(a.z(), b.z());
}

inline bool operator!=(const Tuple& a, const Tuple& b) { return !(a == b); }

inline Tuple operator+(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w());
}

inline Tuple operator-(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w());
}

inline Tuple operator*(const Tuple& a, double b) { return Tuple(a.x() * b, a.y() * b, a.z() * b, a.w() * b); }

inline Tuple operator/(const Tuple& a, double b) { return Tuple(a.x() / b, a.y() / b, a.z() / b, a.w() / b); }

inline std::ostream& operator<<(std::ostream& out, const Tuple& t) {
  out << "(" << t.x() << ", " << t.y() << ", " << t.z() << ", " << t.w() << ")";

  return out;
}

}  // namespace RayTracer

#endif /* C9E0998C_94E3_4D8B_B8FC_1C74D8637378 */
