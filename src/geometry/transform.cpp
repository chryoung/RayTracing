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

Matrix view_transform(const Point& from, const Point& to, const Vector& up) {
  Vector forward = to - from;
  forward.normalize();

  Vector normalized_up = up;
  normalized_up.normalize();

  Vector left = forward.cross(normalized_up);
  Vector true_up = left.cross(forward);
  Matrix orientation = Matrix::unchecked_create(4, 4);

  orientation[0][0] = left.x();
  orientation[0][1] = left.y();
  orientation[0][2] = left.z();
  orientation[0][3] = 0;

  orientation[1][0] = true_up.x();
  orientation[1][1] = true_up.y();
  orientation[1][2] = true_up.z();
  orientation[1][3] = 0;

  orientation[2][0] = -forward.x();
  orientation[2][1] = -forward.y();
  orientation[2][2] = -forward.z();
  orientation[2][3] = 0;

  orientation[3][0] = 0;
  orientation[3][1] = 0;
  orientation[3][2] = 0;
  orientation[3][3] = 1;

  return orientation * translation(-from.x(), -from.y(), -from.z());
}

}  // namespace Transform
}  // namespace RayTracer
