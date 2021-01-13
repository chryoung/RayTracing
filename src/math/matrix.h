#ifndef CA47C3DE_E656_407E_870D_96E6611689C6
#define CA47C3DE_E656_407E_870D_96E6611689C6

#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "tuple.h"
#include "utility/log_helper.h"
#include "utility/utility.h"

namespace RayTracer {
class Matrix {
 public:
  static Matrix create(size_t num_row, size_t num_col) {
    if (num_row == 0 || num_col == 0) {
      throw std::invalid_argument(CURRENT_LINE + " create: num_row or num_col should be greater than 0.");
    }
    return Matrix(num_row, num_col);
  }

  template <class T>
  static Matrix create(std::initializer_list<std::initializer_list<T>> numbers) {
    static_assert(std::is_convertible<T, double>::value, "Matrix::create requires numbers can be converted to double.");

    if (numbers.begin() == numbers.end() || numbers.begin()->begin() == numbers.begin()->end()) {
      throw std::invalid_argument(CURRENT_LINE +
                                  " create: empty std::initializer_list cannot be used to create a Matrix.");
    }

    size_t num_col = 0;
    for (auto iter = numbers.begin()->begin(); iter != numbers.begin()->end(); iter++, num_col++)
      ;

    std::vector<std::vector<double>> matrix_data;
    size_t row = 0;
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++, row++) {
      std::vector<double> matrix_row;
      for (auto row_iter = iter->begin(); row_iter != iter->end(); row_iter++) {
        matrix_row.emplace_back(static_cast<double>(*row_iter));
      }

      if (matrix_row.size() != num_col) {
        throw std::invalid_argument(CURRENT_LINE + " create: the col of the row == " + std::to_string(row) +
                                    " is not equal to the ncol of the first row == " + std::to_string(num_col));
      }

      matrix_data.emplace_back(std::move(matrix_row));
    }

    Matrix matrix;
    matrix._data = std::move(matrix_data);

    return matrix;
  }

  static Matrix unchecked_create(std::initializer_list<std::initializer_list<double>> numbers) {
    Matrix matrix;
    for (auto iter = numbers.begin(); iter != numbers.end(); iter++) {
      matrix._data.emplace_back(*iter);
    }

    return matrix;
  }

  ~Matrix() = default;

  static Matrix id(size_t num_rows) {
    if (num_rows <= 0) {
      throw std::invalid_argument(CURRENT_LINE + " id: num_rows should > 0.");
    }

    Matrix m(num_rows, num_rows);
    for (size_t row = 0; row < num_rows; row++) {
      m[row][row] = 1;
    }

    return m;
  }

  std::vector<double>& operator[](size_t row) { return _data[row]; }
  const std::vector<double>& operator[](size_t row) const { return _data[row]; }

  double at(size_t row, size_t col) {
    if (row >= rows() || col >= cols()) {
      throw std::out_of_range(CURRENT_LINE + " at: index is out of range.");
    }

    return _data[row][col];
  }

  double at(size_t row, size_t col) const {
    if (row >= rows() || col >= cols()) {
      throw std::out_of_range(CURRENT_LINE + " at: index is out of range.");
    }

    return _data[row][col];
  }

  bool is_square() { return rows() == cols(); }
  bool is_square() const { return rows() == cols(); }

  bool multiply_inplace(const Matrix& b) {
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

  bool multiply_inplace(const Tuple& b) {
    Matrix matrix_b = create({
        {b.x()},
        {b.y()},
        {b.z()},
        {b.w()},
    });

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

    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
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

  double determinant() const { return const_cast<Matrix&>(*this).determinant(); }

  bool is_invertible() { return is_double_ne(determinant(), 0); }
  bool is_invertible() const { return is_double_ne(determinant(), 0); }

  Matrix submatrix(size_t row, size_t col) {
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

  Matrix submatrix(size_t row, size_t col) const { return const_cast<Matrix&>(*this).submatrix(row, col); }

  double minor(size_t row, size_t col) {
    auto sub = submatrix(row, col);
    return sub.determinant();
  }

  double minor(size_t row, size_t col) const { return const_cast<Matrix&>(*this).minor(row, col); }

  double cofactor(size_t row, size_t col) {
    auto minor = this->minor(row, col);
    if ((row + col) % 2 == 1) {
      return -minor;
    }

    return minor;
  }

  double cofactor(size_t row, size_t col) const { return const_cast<Matrix&>(*this).cofactor(row, col); }

  Matrix inverse() {
    Matrix companion(rows(), cols());

    auto det = determinant();
    for (size_t row = 0; row < rows(); row++) {
      for (size_t col = 0; col < cols(); col++) {
        companion[row][col] = cofactor(row, col) / det;
      }
    }

    return companion.transpose();
  }

  Matrix inverse() const { return const_cast<Matrix&>(*this).inverse(); }

  size_t rows() { return _data.size(); }
  size_t rows() const { return _data.size(); }
  size_t cols() { return (*this)[0].size(); }
  size_t cols() const { return (*this)[0].size(); }

 private:
  Matrix() {}
  Matrix(size_t num_row, size_t num_col)
      : _data(std::vector<std::vector<double>>(num_row, std::vector<double>(num_col, 0.0))) {}

  std::vector<std::vector<double>> _data;
};

inline bool operator==(const Matrix& a, const Matrix& b) {
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

inline bool operator!=(const Matrix& a, const Matrix& b) { return !(a == b); }

inline Matrix operator*(const Matrix& a, const Matrix b) {
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

inline Tuple operator*(const Matrix& a, const Tuple& b) {
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

inline Point operator*(const Matrix& a, const Point& b) {
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

inline Vector operator*(const Matrix& a, const Vector& b) {
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

inline std::ostream& operator<<(std::ostream& out, const Matrix& m) {
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

#endif /* CA47C3DE_E656_407E_870D_96E6611689C6 */
