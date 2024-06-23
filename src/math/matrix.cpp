#include "matrix.h"
#include "utility/debug.h"

namespace RayTracer {

std::unique_ptr<MemoryPool<double>> Matrix::_mem_pool;

Matrix Matrix::operator-() {
  Matrix minus = Matrix::unchecked_create(rows(), cols());

  Matrix& a = *this;

  for (int r = 0; r < rows(); ++r) {
    for (int c = 0; c < cols(); ++c) {
      minus[r][c] = a[r][c];
    }
  }

  return minus;
}

Matrix Matrix::operator-() const {
  Matrix minus = Matrix::unchecked_create(rows(), cols());

  const Matrix& a = *this;

  for (int r = 0; r < rows(); ++r) {
    for (int c = 0; c < cols(); ++c) {
      minus[r][c] = a[r][c];
    }
  }

  return minus;
}

Matrix Matrix::create(size_t num_row, size_t num_col) {
  if (num_row <= 0 || num_col <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " create: num_row or num_col should be greater than 0.");
  }
  return Matrix(num_row, num_col);
}

Matrix Matrix::unchecked_create(size_t num_row, size_t num_col) {
  return Matrix(num_row, num_col);
}

Matrix Matrix::unchecked_create(int num_row, int num_col, std::initializer_list<std::initializer_list<double>> numbers) {
  Matrix matrix(num_row, num_col);

  int i = 0;
  for (auto row_iter = numbers.begin(); i < num_row; ++i, ++row_iter) {
    int j = 0;
    for (auto col_iter = row_iter->begin(); j < num_col; ++j, ++col_iter) {
      matrix._data[i * num_col + j] = *col_iter;
    }
  }

  return matrix;
}

Matrix Matrix::id(size_t num_rows) {
  if (num_rows <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " id: num_rows should > 0.");
  }

  Matrix m(num_rows, num_rows);
  for (size_t row = 0; row < num_rows; row++) {
    for (size_t col = 0; col < num_rows; col++) {
        m[row][col] = row == col ? 1 : 0;
    }
  }

  return m;
}

Matrix Matrix::zero(size_t num_row, size_t num_col) {
  if (num_row <= 0 || num_col <= 0) {
    throw std::invalid_argument(CURRENT_LINE + " id: num_row and num_col should > 0.");
  }

  Matrix m(num_row, num_col);
  for (size_t row = 0; row < num_row; row++) {
    for (size_t col = 0; col < num_col; col++) {
        m[row][col] = 0;
    }
  }

  return m;
}

double* Matrix::operator[](size_t row) { return _data + row * _num_col; }

const double* Matrix::operator[](size_t row) const { return _data + row * _num_col; }

double Matrix::at(size_t row, size_t col) const {
  if (row >= rows() || col >= cols()) {
    throw std::out_of_range(CURRENT_LINE + " at: index is out of range.");
  }

  return _data[row * _num_col + col];
}

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

  *this = std::move(product);

  return true;
}

bool Matrix::multiply_inplace(const Tuple& b) {
  Matrix matrix_b = unchecked_create(4, 1, {
      {b.x()},
      {b.y()},
      {b.z()},
      {b.w()},
  });

  return multiply_inplace(matrix_b);
}

bool Matrix::multiply_to_tuple(const Tuple& b, Tuple& out_product) const {
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

Matrix Matrix::transpose() const {
  Matrix t(cols(), rows());

  for (size_t row = 0; row < rows(); row++) {
    for (size_t col = 0; col < cols(); col++) {
      t[col][row] = (*this)[row][col];
    }
  }

  return t;
}

void Matrix::transpose_inplace() {
  auto t = transpose();
  *this = std::move(t);
}

double Matrix::determinant() const {
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

bool Matrix::is_invertible() const { return is_double_ne(determinant(), 0); }

Matrix Matrix::submatrix(size_t row, size_t col) const {
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

double Matrix::minor(size_t row, size_t col) const {
  auto sub = submatrix(row, col);
  return sub.determinant();
}

double Matrix::cofactor(size_t row, size_t col) const {
  auto minor = this->minor(row, col);
  if ((row + col) % 2 == 1) {
    return -minor;
  }

  return minor;
}

Matrix Matrix::inverse() const {
  if (rows() != cols()) {
    throw std::runtime_error("Non-square matrix is not invertible");
  }

  const Matrix& a = *this;

  if (rows() == 2) {
    double det = a[0][0] * a[1][1] - a[0][1] * a[1][0];

    Matrix inv = Matrix::unchecked_create(2, 2);

    inv[0][0] =  a[1][1] / det;
    inv[0][1] = -a[1][0] / det;
    inv[1][0] = -a[0][1] / det;
    inv[0][1] =  a[0][0] / det;

    return inv;
  }

  if (rows() == 3) {
    double det = a[0][0] * a[1][1] * a[2][2] +
                 a[0][1] * a[1][2] * a[2][0] +
                 a[0][2] * a[1][0] * a[2][1] -
                 a[0][0] * a[1][2] * a[2][1] -
                 a[0][1] * a[1][0] * a[2][2] -
                 a[0][2] * a[1][1] * a[2][0];

    Matrix inv = Matrix::unchecked_create(3, 3);

    inv[0][0] =  (a[1][1] * a[2][2] - a[1][2] * a[2][1]) / det;
    inv[0][1] = -(a[0][1] * a[2][2] - a[0][2] * a[2][1]) / det;
    inv[0][2] =  (a[0][1] * a[1][2] - a[0][2] * a[1][1]) / det;

    inv[1][0] = -(a[1][0] * a[2][2] - a[1][2] * a[2][0]) / det;
    inv[1][1] =  (a[0][0] * a[2][2] - a[0][2] * a[2][0]) / det;
    inv[1][2] = -(a[0][0] * a[1][2] - a[0][2] * a[1][0]) / det;

    inv[2][0] =  (a[1][0] * a[2][1] - a[1][1] * a[2][0]) / det;
    inv[2][1] = -(a[0][0] * a[2][1] - a[0][1] * a[2][0]) / det;
    inv[2][2] =  (a[0][0] * a[1][1] - a[0][1] * a[1][0]) / det;

    return inv;
  }

  if (rows() == 4 &&
      is_double_eq(a[3][0], 0) &&
      is_double_eq(a[3][1], 0) &&
      is_double_eq(a[3][2], 0) &&
      is_double_eq(a[3][3], 1)) {
    Matrix M = Matrix::unchecked_create(3, 3);
    for (int r = 0; r < 3; ++r) {
      for (int c = 0; c < 3; ++c) {
        M[r][c] = a[r][c];
      }
    }

    Vector b{a[0][3], a[1][3], a[2][3]};

    Matrix M_inv = M.inverse();

    Vector M_inv_b = -(M_inv * b);

    Matrix inv = Matrix::unchecked_create(4, 4);

    for (int r = 0; r < 3; ++r) {
      for (int c = 0; c < 3; ++c) {
        inv[r][c] = M_inv[r][c];
      }
    }

    inv[0][3] = M_inv_b.x();
    inv[1][3] = M_inv_b.y();
    inv[2][3] = M_inv_b.z();

    inv[3][0] = 0;
    inv[3][1] = 0;
    inv[3][2] = 0;
    inv[3][3] = 1;

    return inv;
  }


  Matrix companion(rows(), cols());
  auto det = determinant();

  for (size_t row = 0; row < rows(); row++) {
    for (size_t col = 0; col < cols(); col++) {
      companion[row][col] = cofactor(row, col) / det;
    }
  }

  return companion.transpose();
}

size_t Matrix::rows() const { return _num_row; }

size_t Matrix::cols() const { return _num_col; }

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

  Matrix product = Matrix::zero(a.rows(), b.cols());
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
  if (!a.is_square() || !(a.rows() == Tuple::TUPLE_DIMENSIONS || a.rows() == 3)) {
    throw std::runtime_error(
        CURRENT_LINE +
        " operator*: Matrix multiplication cannot be performed because a's dimension is not compatible with Vector.");
  }

  Vector product; // Vector.w is always 0
  double x = b.x();
  double y = b.y();
  double z = b.z();
  product.set_x(x * a[0][0] + y * a[0][1] + z * a[0][2]);
  product.set_y(x * a[1][0] + y * a[1][1] + z * a[1][2]);
  product.set_z(x * a[2][0] + y * a[2][1] + z * a[2][2]);

  return product;
}

std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  out << "{\n";
  for (size_t row = 0; row < m.rows(); row++) {
    out << "  {";
    for (size_t col = 0; col < m.cols() - 1; col++) {
      out << m[row][col] << ", ";
    }
    out << m[row][m.cols() - 1] << "},\n";
  }
  out << "}";

  return out;
}
}  // namespace RayTracer
