#ifndef C9E0998C_94E3_4D8B_B8FC_1C74D8637378
#define C9E0998C_94E3_4D8B_B8FC_1C74D8637378

#include <cmath>
#include <utility>

#include "utility.h"

namespace RayTracing {
class Tuple {
 public:
  Tuple(float x, float y, float z, float w) : _x(x), _y(y), _z(z), _w(w) {}
  Tuple() : Tuple(0, 0, 0, 0) {}
  Tuple(const Tuple& other) = default;
  Tuple(Tuple&& other) = default;
  Tuple& operator=(const Tuple& other) = default;
  Tuple& operator=(Tuple&& other) = default;

  static constexpr float POINT_W = 1.0;
  static constexpr float VECTOR_W = 0.0;

  static Tuple make_point(float x, float y, float z) {
    return Tuple(x, y, z, POINT_W);
  }

  static Tuple make_vector(float x, float y, float z) {
    return Tuple(x, y, z, VECTOR_W);
  }

  float x() { return _x; }
  float y() { return _y; }
  float z() { return _z; }
  float w() { return _w; }

  float x() const { return _x; }
  float y() const { return _y; }
  float z() const { return _z; }
  float w() const { return _w; }

  Tuple& set_x(float x) {
    _x = x;

    return *this;
  }

  Tuple& set_y(float y) {
    _y = y;

    return *this;
  }

  Tuple& set_z(float z) {
    _z = z;

    return *this;
  }

  Tuple& set_w(float w) {
    _w = w;

    return *this;
  }

  float magnitude() { return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w); }

  float magnitude() const {
    return std::sqrt(_x * _x + _y * _y + _z * _z + _w * _w);
  }

  void normalize() {
    float m = magnitude();
    _x = _x / m;
    _y = _y / m;
    _z = _z / m;
    _w = _w / m;
  }

  bool is_point() { return is_float_eq(_w, POINT_W); }
  bool is_point() const { return is_float_eq(_w, POINT_W); }

  bool is_vector() { return is_float_eq(_w, VECTOR_W); }
  bool is_vector() const { return is_float_eq(_w, VECTOR_W); }

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

  float dot(const Tuple& other) {
    return _x * other._x + _y * other._y + _z * other._z + _w * other._w;
  }

  Tuple cross(const Tuple& other) {
    return make_vector(_y * other._z - _z * other._y,
                       _z * other._x - _x * other._z,
                       _x * other._y - _y * other._x);
  }

 private:
  float _x;
  float _y;
  float _z;
  float _w;
};

inline bool operator==(const Tuple& a, const Tuple& b) {
  return is_float_eq(a.w(), b.w()) && is_float_eq(a.x(), b.x()) &&
         is_float_eq(a.y(), b.y()) && is_float_eq(a.z(), b.z());
}

inline bool operator!=(const Tuple& a, const Tuple& b) { return !(a == b); }

inline Tuple operator+(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w());
}

inline Tuple operator-(const Tuple& a, const Tuple& b) {
  return Tuple(a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w());
}

inline Tuple operator*(const Tuple& a, float b) {
  return Tuple(a.x() * b, a.y() * b, a.z() * b, a.w() * b);
}

inline Tuple operator/(const Tuple& a, float b) {
  return Tuple(a.x() / b, a.y() / b, a.z() / b, a.w() / b);
}

}  // namespace RayTracing

#endif /* C9E0998C_94E3_4D8B_B8FC_1C74D8637378 */
