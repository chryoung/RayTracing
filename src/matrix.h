#ifndef CA47C3DE_E656_407E_870D_96E6611689C6
#define CA47C3DE_E656_407E_870D_96E6611689C6

#include <initializer_list>
#include <utility>
#include <vector>
#include <ostream>

#include "tuple.h"
#include "utility.h"

namespace RayTracer {
class Matrix {
 public:
  Matrix(int num_row, int num_col) {
    if (num_row > 0 && num_col > 0) {
      _data = std::vector<std::vector<double>>(num_row, std::vector<double>(num_col, 0.0));
    } else {
      _data = std::vector<std::vector<double>>(1, std::vector<double>(1, 0.0));
    }
  }

  Matrix(std::initializer_list<std::initializer_list<double>> numbers) {
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
      _data.emplace_back(*iter);
    }
  }

  ~Matrix() {}

  static Matrix id(int num_rows) {
    if (num_rows <= 0) {
      num_rows = 1;
    }

    Matrix m(num_rows, num_rows);
    for (int row = 0; row < num_rows; row++) {
      m[row][row] = 1;
    }

    return m;
  }

  std::vector<double>& operator[](size_t row) { return _data[row]; }
  const std::vector<double>& operator[](size_t row) const { return _data[row]; }

  bool is_square() { return rows() == cols(); }
  bool is_square() const { return rows() == cols(); }

  bool multiply_inplace(const Matrix& b) {
    if (cols() != b.rows()) {
      return false;
    }

    Matrix product(rows(), b.cols());
    for (int row = 0; row < rows(); ++row) {
      for (int col = 0; col < b.cols(); ++col) {
        for (int i = 0; i < cols(); ++i) {
          product[row][col] += (*this)[row][i] * b[i][col];
        }
      }
    }

    _data = std::move(product._data);

    return true;
  }

  bool multiply_inplace(const Tuple& b) {
    Matrix matrix_b{
        {b.x()},
        {b.y()},
        {b.z()},
        {b.w()},
    };

    return multiply_inplace(matrix_b);
  }

  bool multiply_to_tuple(const Tuple& b, Tuple& out_product) {
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

  Matrix transpose() {
    Matrix t(cols(), rows());

    for (int row = 0; row < rows(); row++) {
      for (int col = 0; col < cols(); col++) {
        t[col][row] = (*this)[row][col];
      }
    }

    return t;
  }

  Matrix transpose() const { return const_cast<Matrix&>(*this).transpose(); }

  void transpose_inplace() {
    auto t = transpose();
    _data = std::move(t._data);
  }

  double determinant() {
    if (!is_square()) {
      return 0;
    }

    if (rows() == 2) {
      return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
    } else {
      double det = 0;
      for (int col = 0; col < cols(); col++) {
        det += (*this)[0][col] * cofactor(0, col);
      }
      return det;
    }
  }

  double determinant() const {
    return const_cast<Matrix&>(*this).determinant();
  }

  bool is_invertible() { return is_double_ne(determinant(), 0); }
  bool is_invertible() const { return is_double_ne(determinant(), 0); }

  Matrix submatrix(int row, int col) {
    if (row < 0 || col < 0 || row >= rows() || col >= cols()) {
      return Matrix(1, 1);
    }

    Matrix s(rows() - 1, cols() - 1);
    for (int r = 0; r < row; r++) {
      for (int c = 0; c < col; c++) {
        s[r][c] = (*this)[r][c];
      }
    }

    for (int r = row + 1; r < rows(); r++) {
      for (int c = 0; c < col; c++) {
        s[r - 1][c] = (*this)[r][c];
      }
    }

    for (int r = 0; r < row; r++) {
      for (int c = col + 1; c < cols(); c++) {
        s[r][c - 1] = (*this)[r][c];
      }
    }

    for (int r = row + 1; r < rows(); r++) {
      for (int c = col + 1; c < cols(); c++) {
        s[r - 1][c - 1] = (*this)[r][c];
      }
    }

    return s;
  }

  Matrix submatrix(int row, int col) const { return const_cast<Matrix&>(*this).submatrix(row, col); }

  double minor(int row, int col) {
    auto sub = submatrix(row, col);
    return sub.determinant();
  }

  double minor(int row, int col) const { return const_cast<Matrix&>(*this).minor(row, col); }

  double cofactor(int row, int col) {
    auto minor = this->minor(row, col);
    if ((row + col) % 2 == 1) {
      return -minor;
    }

    return minor;
  }

  double cofactor(int row, int col) const { return const_cast<Matrix&>(*this).cofactor(row, col); }

  Matrix inverse() {
    Matrix companion(rows(), cols());

    auto det = determinant();
    for (int row = 0; row < rows(); row++) {
      for (int col = 0; col < cols(); col++) {
        companion[row][col] = cofactor(row, col) / det;
      }
    }

    return companion.transpose();
  }

  Matrix inverse() const {
    return const_cast<Matrix&>(*this).inverse();
  }

  int rows() { return _data.size(); }
  int rows() const { return _data.size(); }
  int cols() { return (*this)[0].size(); }
  int cols() const { return (*this)[0].size(); }

 private:
  std::vector<std::vector<double>> _data;
};

inline bool operator==(const Matrix& a, const Matrix& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols()) {
    return false;
  }

  for (int row = 0; row < a.rows(); ++row) {
    for (int col = 0; col < a.cols(); ++col) {
      if (!is_double_eq(a[row][col], b[row][col])) {
        return false;
      }
    }
  }

  return true;
}

inline bool operator!=(const Matrix& a, const Matrix& b) { return !(a == b); }

inline Matrix operator*(const Matrix& a, const Matrix b) {
  if (a.cols() != b.rows()) {
    return a;  // throw std::runtime_exception("a.cols() != b.rows()");
  }

  Matrix product(a.rows(), b.cols());
  for (int row = 0; row < a.rows(); ++row) {
    for (int col = 0; col < b.cols(); ++col) {
      for (int i = 0; i < a.cols(); ++i) {
        product[row][col] += a[row][i] * b[i][col];
      }
    }
  }

  return product;
}

inline Tuple operator*(const Matrix& a, const Tuple& b) {
  if (!a.is_square() || a.rows() != Tuple::TUPLE_DIMENSIONS) {
    return b;
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

inline std::ostream& operator<<(std::ostream& out, const Matrix& m) {
  out << "{\n";
  for (int row = 0; row < m.rows(); row++) {
    out << "{";
    for (int col = 0; col < m.cols() - 1; col++) {
      out << m[row][col] << ", ";
    }
    out << m[row][m.cols() - 1] << "},\n";
  }
  out << "}";

  return out;
}
}  // namespace RayTracer

#endif /* CA47C3DE_E656_407E_870D_96E6611689C6 */
