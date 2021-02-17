#ifndef A77EC4CF_3024_41BB_BC18_66768AB4962D
#define A77EC4CF_3024_41BB_BC18_66768AB4962D

#include <cmath>

#include "math/matrix.h"
#include "math/tuple.h"

namespace RayTracer {
namespace Transform {

constexpr int TRANSFORMATION_MATRIX_ROWS = 4;

Matrix translating(double x, double y, double z);
Matrix scaling(double x, double y, double z);
Matrix rotation_x(double radians);
Matrix rotation_y(double radians);
Matrix rotation_z(double radians);
Matrix shearing(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

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
