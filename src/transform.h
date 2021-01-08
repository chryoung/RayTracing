#ifndef A77EC4CF_3024_41BB_BC18_66768AB4962D
#define A77EC4CF_3024_41BB_BC18_66768AB4962D

#include <cmath>

#include "matrix.h"
#include "tuple.h"

namespace RayTracer {
namespace Transform {
inline Matrix translating(double x, double y, double z) {
  return Matrix::unchecked_create({
      {1, 0, 0, x},
      {0, 1, 0, y},
      {0, 0, 1, z},
      {0, 0, 0, 1},
  });
}

inline Matrix scaling(double x, double y, double z) {
  return Matrix::unchecked_create({
      {x, 0, 0, 0},
      {0, y, 0, 0},
      {0, 0, z, 0},
      {0, 0, 0, 1},
  });
}

inline Matrix rotation_x(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create({
      {1, 0, 0, 0},
      {0, cos_r, -sin_r, 0},
      {0, sin_r, cos_r, 0},
      {0, 0, 0, 1},
  });
}

inline Matrix rotation_y(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create({
      {cos_r, 0, sin_r, 0},
      {0, 1, 0, 0},
      {-sin_r, 0, cos_r, 0},
      {0, 0, 0, 1},
  });
}

inline Matrix rotation_z(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create({
      {cos_r, -sin_r, 0, 0},
      {sin_r, cos_r, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
  });
}

inline Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
  return Matrix::unchecked_create({
      {1, x_y, x_z, 0},
      {y_x, 1, y_z, 0},
      {z_x, z_y, 1, 0},
      {0, 0, 0, 1},
  });
}

class TransformationBuilder {
 public:
  TransformationBuilder() : _transformation_matrix(Matrix::id(Tuple::TUPLE_DIMENSIONS)) {}
  ~TransformationBuilder() {}
  TransformationBuilder& translate(double x, double y, double z) {
    _transformation_matrix = translating(x, y, z) * _transformation_matrix;

    return *this;
  }

  TransformationBuilder& scale(double x, double y, double z) {
    _transformation_matrix = scaling(x, y, z) * _transformation_matrix;

    return *this;
  }

  TransformationBuilder& rotate_x(double radians) {
    _transformation_matrix = rotation_x(radians) * _transformation_matrix;

    return *this;
  }

  TransformationBuilder& rotate_y(double radians) {
    _transformation_matrix = rotation_y(radians) * _transformation_matrix;

    return *this;
  }

  TransformationBuilder& rotate_z(double radians) {
    _transformation_matrix = rotation_z(radians) * _transformation_matrix;

    return *this;
  }

  TransformationBuilder& shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
    _transformation_matrix = shearing(x_y, x_z, y_x, y_z, z_x, z_y) * _transformation_matrix;

    return *this;
  }

  Matrix build() { return _transformation_matrix; }

  Matrix build() const { return _transformation_matrix; }

 private:
  Matrix _transformation_matrix;
};
}  // namespace Transform
}  // namespace RayTracer

#endif /* A77EC4CF_3024_41BB_BC18_66768AB4962D */
