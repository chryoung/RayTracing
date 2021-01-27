#include "matrix.h"

namespace RayTracer {
Matrix Matrix::create(size_t num_row, size_t num_col) {
  if (num_row == 0 || num_col == 0) {
    throw std::invalid_argument(CURRENT_LINE + " create: num_row or num_col should be greater than 0.");
  }
  return Matrix(num_row, num_col);
}

Matrix Matrix::unchecked_create(std::initializer_list<std::initializer_list<double>> numbers) {
  Matrix matrix;
  for (auto iter = numbers.begin(); iter != numbers.end(); iter++) {
    matrix._data.emplace_back(*iter);
  }

  return matrix;
}

Matrix Matrix::id(size_t num_rows) {
  if (num_rows <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " id: num_rows should > 0.");
  }

  Matrix m(num_rows, num_rows);
  for (size_t row = 0; row < num_rows; row++) {
    m[row][row] = 1;
  }

  return m;
}

std::vector<double>& Matrix::operator[](size_t row) { return _data[row]; }

const std::vector<double>& Matrix::operator[](size_t row) const { return _data[row]; }

double Matrix::at(size_t row, size_t col) {
  if (row >= rows() || col >= cols()) {
    throw std::out_of_range(CURRENT_LINE + " at: index is out of range.");
  }

  return _data[row][col];
}

double Matrix::at(size_t row, size_t col) const {
  if (row >= rows() || col >= cols()) {
    throw std::out_of_range(CURRENT_LINE + " at: index is out of range.");
  }

  return _data[row][col];
}

bool Matrix::is_square() { return rows() == cols(); }

bool Matrix::is_square() const { return rows() == cols(); }

bool Matrix::multiply_inplace(const Matrix& b) {
  if (cols() != b.rows()) {
    return false;
  }

  Matrix product(rows(), b.cols());
  for (size_t row = 0; row < rows(); ++row) {
    for (size_t col = 0; col < b.cols(); ++col) {
      for (size_t i = 0; i < cols(); ++i) {
        product[row][col] += (*this)[row][i] * b[i][col];
      }
    }
  }

  _data = std::move(product._data);

  return true;
}

bool Matrix::multiply_inplace(const Tuple& b) {
  Matrix matrix_b = create({
      {b.x()},
      {b.y()},
      {b.z()},
      {b.w()},
  });

  return multiply_inplace(matrix_b);
}

bool Matrix::multiply_to_tuple(const Tuple& b, Tuple& out_product) {
  if (cols() != Tuple::TUPLE_DIMENSIONS || !is_square()) {
    return false;
  }

  double x = b.x();
  double y = b.y();
  double z = b.z();
  double w = b.w();
  out_product.set_x(x * (*this)[0][0] + y * (*this)[0][1] + z * (*this)[0][2] + w * (*this)[0][3]);
  out_product.set_y(x * (*this)[1][0] + y * (*this)[1][1] + z * (*this)[1][2] + w * (*this)[1][3]);
  out_product.set_z(x * (*this)[2][0] + y * (*this)[2][1] + z * (*this)[2][2] + w * (*this)[2][3]);
  out_product.set_w(x * (*this)[3][0] + y * (*this)[3][1] + z * (*this)[3][2] + w * (*this)[3][3]);

  return true;
}

Matrix Matrix::transpose() {
  Matrix t(cols(), rows());

  for (size_t row = 0; row < rows(); row++) {
    for (size_t col = 0; col < cols(); col++) {
      t[col][row] = (*this)[row][col];
    }
  }

  return t;
}

Matrix Matrix::transpose() const { return const_cast<Matrix&>(*this).transpose(); }

void Matrix::transpose_inplace() {
  auto t = transpose();
  _data = std::move(t._data);
}

double Matrix::determinant() {
  if (!is_square()) {
    throw std::runtime_error(CURRENT_LINE + " determinant: non-square matrix cannot have determinant.");
  }

  if (rows() == 2) {
    return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
  } else {
    double det = 0;
    for (size_t col = 0; col < cols(); col++) {
      det += (*this)[0][col] * cofactor(0, col);
    }
    return det;
  }
}

double Matrix::determinant() const { return const_cast<Matrix&>(*this).determinant(); }

bool Matrix::is_invertible() { return is_double_ne(determinant(), 0); }

bool Matrix::is_invertible() const { return is_double_ne(determinant(), 0); }

Matrix Matrix::submatrix(size_t row, size_t col) {
  if (row < 0 || col < 0 || row >= rows() || col >= cols()) {
    throw std::invalid_argument(CURRENT_LINE + " submatrix: invalid row or col");
  }

  Matrix s(rows() - 1, cols() - 1);
  for (size_t r = 0; r < row; r++) {
    for (size_t c = 0; c < col; c++) {
      s[r][c] = (*this)[r][c];
    }
  }

  for (size_t r = row + 1; r < rows(); r++) {
    for (size_t c = 0; c < col; c++) {
      s[r - 1][c] = (*this)[r][c];
    }
  }

  for (size_t r = 0; r < row; r++) {
    for (size_t c = col + 1; c < cols(); c++) {
      s[r][c - 1] = (*this)[r][c];
    }
  }

  for (size_t r = row + 1; r < rows(); r++) {
    for (size_t c = col + 1; c < cols(); c++) {
      s[r - 1][c - 1] = (*this)[r][c];
    }
  }

  return s;
}

Matrix Matrix::submatrix(size_t row, size_t col) const { return const_cast<Matrix&>(*this).submatrix(row, col); }

double Matrix::minor(size_t row, size_t col) {
  auto sub = submatrix(row, col);
  return sub.determinant();
}

double Matrix::minor(size_t row, size_t col) const { return const_cast<Matrix&>(*this).minor(row, col); }

double Matrix::cofactor(size_t row, size_t col) {
  auto minor = this->minor(row, col);
  if ((row + col) % 2 == 1) {
    return -minor;
  }

  return minor;
}

double Matrix::cofactor(size_t row, size_t col) const { return const_cast<Matrix&>(*this).cofactor(row, col); }

Matrix Matrix::inverse() {
  Matrix companion(rows(), cols());

  auto det = determinant();
  for (size_t row = 0; row < rows(); row++) {
    for (size_t col = 0; col < cols(); col++) {
      companion[row][col] = cofactor(row, col) / det;
    }
  }

  return companion.transpose();
}

Matrix Matrix::inverse() const { return const_cast<Matrix&>(*this).inverse(); }

size_t Matrix::rows() { return _data.size(); }

size_t Matrix::rows() const { return _data.size(); }

size_t Matrix::cols() { return (*this)[0].size(); }

size_t Matrix::cols() const { return (*this)[0].size(); }

bool operator==(const Matrix& a, const Matrix& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for (size_t row = 0; row < a.rows(); ++row) {
    for (size_t col = 0; col < a.cols(); ++col) {
      if (!is_double_eq(a[row][col], b[row][col])) {
        return false;
      }
    }
  }

  return true;
}

bool operator!=(const Matrix& a, const Matrix& b) { return !(a == b); }

Matrix operator*(const Matrix& a, const Matrix& b) {
  if (a.cols() != b.rows()) {
    throw std::runtime_error(CURRENT_LINE +
                             " operator*: Matrix multiplication cannot be performed because a.cols() != b.rows()");
  }

  Matrix product = Matrix::create(a.rows(), b.cols());
  for (size_t row = 0; row < a.rows(); ++row) {
    for (size_t col = 0; col < b.cols(); ++col) {
      for (size_t i = 0; i < a.cols(); ++i) {
        product[row][col] += a[row][i] * b[i][col];
      }
    }
  }

  return product;
}

Tuple operator*(const Matrix& a, const Tuple& b) {
  if (!a.is_square() || a.rows() != Tuple::TUPLE_DIMENSIONS) {
    throw std::runtime_error(
        CURRENT_LINE +
        " operator*: Matrix multiplication cannot be performed because a's dimension is not compatible with Tuple.");
  }

  Tuple product;
  double x = b.x();
  double y = b.y();
  double z = b.z();
  double w = b.w();
  product.set_x(x * a[0][0] + y * a[0][1] + z * a[0][2] + w * a[0][3]);
  product.set_y(x * a[1][0] + y * a[1][1] + z * a[1][2] + w * a[1][3]);
  product.set_z(x * a[2][0] + y * a[2][1] + z * a[2][2] + w * a[2][3]);
  product.set_w(x * a[3][0] + y * a[3][1] + z * a[3][2] + w * a[3][3]);

  return product;
}

Point operator*(const Matrix& a, const Point& b) {
  if (!a.is_square() || a.rows() != Tuple::TUPLE_DIMENSIONS) {
    throw std::runtime_error(
        CURRENT_LINE +
        " operator*: Matrix multiplication cannot be performed because a's dimension is not compatible with Point.");
  }

  Point product;
  double x = b.x();
  double y = b.y();
  double z = b.z();
  double w = b.w();
  product.set_x(x * a[0][0] + y * a[0][1] + z * a[0][2] + w * a[0][3]);
  product.set_y(x * a[1][0] + y * a[1][1] + z * a[1][2] + w * a[1][3]);
  product.set_z(x * a[2][0] + y * a[2][1] + z * a[2][2] + w * a[2][3]);

  return product;
}

Vector operator*(const Matrix& a, const Vector& b) {
  if (!a.is_square() || a.rows() != Tuple::TUPLE_DIMENSIONS) {
    throw std::runtime_error(
        CURRENT_LINE +
        " operator*: Matrix multiplication cannot be performed because a's dimension is not compatible with Vector.");
  }

  Vector product;
  double x = b.x();
  double y = b.y();
  double z = b.z();
  double w = b.w();
  product.set_x(x * a[0][0] + y * a[0][1] + z * a[0][2] + w * a[0][3]);
  product.set_y(x * a[1][0] + y * a[1][1] + z * a[1][2] + w * a[1][3]);
  product.set_z(x * a[2][0] + y * a[2][1] + z * a[2][2] + w * a[2][3]);

  return product;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  out << "{\n";
  for (size_t row = 0; row < m.rows(); row++) {
    out << "{";
    for (size_t col = 0; col < m.cols() - 1; col++) {
      out << m[row][col] << ", ";
    }
    out << m[row][m.cols() - 1] << "},\n";
  }
  out << "}";

  return out;
}
}  // namespace RayTracer
