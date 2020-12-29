#include "utility.h"

namespace RayTracing {
  class Tuple {
    public:
      static constexpr float POINT_W = 1.0;
      static constexpr float VECTOR_W = 0.0;
      static Tuple* make_tuple(float x, float y, float z, float w) {
        if (!is_valid_w(w)) {
          return nullptr;
        }

        return new Tuple(x, y, z, w);
      }

      static Tuple* make_point(float x, float y, float z) {
        return new Tuple(x, y, z, POINT_W);
      }

      static Tuple* make_vector(float x, float y, float z) {
        return new Tuple(x, y, z, VECTOR_W);
      }

      float x() { return _x; }
      float y() { return _y; }
      float z() { return _z; }
      float w() { return _w; }

      bool set_x(float x) {
        _x = x;

        return true;
      }

      bool set_y(float y){
        _y = y;

        return true;
      }

      bool set_z(float z){
        _z = z;

        return true;
      }

      bool set_w(float w){
        if (!is_valid_w(w)) {
          return false;
        }

        _w = w;

        return true;
      }

      bool is_point() {
        return is_float_eq(_w, POINT_W);
      }

      bool is_vector() {
        return is_float_eq(_w, VECTOR_W);
      }
    private:
      Tuple(float x, float y, float z, float w):
        _x(x),
        _y(y),
        _z(z),
        _w(w) {}

      static bool is_valid_w(float w) {
        return is_float_eq(w, POINT_W) || is_float_eq(w, VECTOR_W);
      }
      float _x;
      float _y;
      float _z;
      float _w;
  };
} // namespace RayTracing
