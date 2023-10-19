#include "transform.h"

namespace RayTracer {
namespace Transform {

Matrix id() {
  return Matrix::id(Transform::TRANSFORMATION_MATRIX_ROWS);
}

Matrix translation(double x, double y, double z) {
  return Matrix::unchecked_create(4, 4, {
      {1, 0, 0, x},
      {0, 1, 0, y},
      {0, 0, 1, z},
      {0, 0, 0, 1},
  });
}

Matrix scaling(double x, double y, double z) {
  return Matrix::unchecked_create(4, 4, {
      {x, 0, 0, 0},
      {0, y, 0, 0},
      {0, 0, z, 0},
      {0, 0, 0, 1},
  });
}

Matrix rotation_x(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create(4, 4, {
      {1, 0, 0, 0},
      {0, cos_r, -sin_r, 0},
      {0, sin_r, cos_r, 0},
      {0, 0, 0, 1},
  });
}

Matrix rotation_y(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create(4, 4, {
      {cos_r, 0, sin_r, 0},
      {0, 1, 0, 0},
      {-sin_r, 0, cos_r, 0},
      {0, 0, 0, 1},
  });
}

Matrix rotation_z(double radians) {
  double cos_r = cos(radians);
  double sin_r = sin(radians);

  return Matrix::unchecked_create(4, 4, {
      {cos_r, -sin_r, 0, 0},
      {sin_r, cos_r, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1},
  });
}

Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
  return Matrix::unchecked_create(4, 4, {
      {1, x_y, x_z, 0},
      {y_x, 1, y_z, 0},
      {z_x, z_y, 1, 0},
      {0, 0, 0, 1},
  });
}

}  // namespace Transform
}  // namespace RayTracer
