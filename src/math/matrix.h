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
  ~Matrix() = default;

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

  static Matrix create(size_t num_row, size_t num_col);
  static Matrix unchecked_create(std::initializer_list<std::initializer_list<double>> numbers);
  static Matrix id(size_t num_rows);
  std::vector<double>& operator[](size_t row);
  const std::vector<double>& operator[](size_t row) const;
  double at(size_t row, size_t col);
  double at(size_t row, size_t col) const;
  bool is_square();
  bool is_square() const;
  bool multiply_inplace(const Matrix& b);
  bool multiply_inplace(const Tuple& b);
  bool multiply_to_tuple(const Tuple& b, Tuple& out_product);
  Matrix transpose();
  Matrix transpose() const;
  void transpose_inplace();
  double determinant();
  double determinant() const;
  bool is_invertible();
  bool is_invertible() const;
  Matrix submatrix(size_t row, size_t col);
  Matrix submatrix(size_t row, size_t col) const;
  double minor(size_t row, size_t col);
  double minor(size_t row, size_t col) const;
  double cofactor(size_t row, size_t col);
  double cofactor(size_t row, size_t col) const;
  Matrix inverse();
  Matrix inverse() const;
  size_t rows();
  size_t rows() const;
  size_t cols();
  size_t cols() const;

 private:
  Matrix() = default;
  Matrix(size_t num_row, size_t num_col)
      : _data(std::vector<std::vector<double>>(num_row, std::vector<double>(num_col, 0.0))) {}

  std::vector<std::vector<double>> _data;
};

bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);
Tuple operator*(const Matrix& a, const Tuple& b);
Point operator*(const Matrix& a, const Point& b);
Vector operator*(const Matrix& a, const Vector& b);
std::ostream& operator<<(std::ostream& out, const Matrix& m);
}  // namespace RayTracer

#endif /* CA47C3DE_E656_407E_870D_96E6611689C6 */
