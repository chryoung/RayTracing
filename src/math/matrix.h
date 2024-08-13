#pragma once
#include <initializer_list>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "tuple.h"
#include "utility/log_helper.h"
#include "utility/utility.h"
#include "utility/memory_pool.h"

namespace RayTracer {

class Matrix {
 public:
  ~Matrix() {
    if (_data != nullptr) {
      _mem_pool->free(_assigned_mem);
      _assigned_mem = nullptr;
      _data = nullptr;
    }
  }

  Matrix(const Matrix& orig) {
    _num_row = orig._num_row;
    _num_col = orig._num_col;
    _assigned_mem = _mem_pool->alloc();
    _data = _assigned_mem->get();
    if (orig._data != nullptr) {
      for (int i = 0; i < _num_row; ++i) {
        for (int j = 0; j < _num_col; ++j) {
          _data[i * _num_col + j] = orig._data[i * _num_col + j];
        }
      }
    }
  }

  Matrix(Matrix&& orig) noexcept {
    _num_row = orig._num_row;
    _num_col = orig._num_col;
    _assigned_mem = orig._assigned_mem;
    _data = orig._data;

    orig._num_row = 0;
    orig._num_col = 0;
    orig._data = nullptr;
    orig._assigned_mem = nullptr;
  }

  Matrix& operator=(const Matrix& orig) {
    if (this != &orig) {
      if (_data != nullptr) {
        _mem_pool->free(_assigned_mem);
        _assigned_mem = nullptr;
        _data = nullptr;
      }

      _num_row = orig._num_row;
      _num_col = orig._num_col;
      if (orig._data != nullptr) {
        _assigned_mem = _mem_pool->alloc();
        _data = _assigned_mem->get();
        for (int i = 0; i < _num_row; ++i) {
          for (int j = 0; j < _num_row; ++j) {
            _data[i * _num_col + j] = orig._data[i * _num_col + j];
          }
        }
      }
    }

    return *this;
  }

  Matrix& operator=(Matrix&& orig) noexcept {
    if (this != &orig) {
      if (_data != nullptr) {
        _mem_pool->free(_assigned_mem);
        _assigned_mem = nullptr;
        _data = nullptr;
      }

      _num_row = orig._num_row;
      _num_col = orig._num_col;
      _data = orig._data;
      _assigned_mem = orig._assigned_mem;

      orig._num_row = 0;
      orig._num_col = 0;
      orig._data = nullptr;
      orig._assigned_mem = nullptr;
    }

    return *this;
  }

  template <class T>
  static Matrix create(std::initializer_list<std::initializer_list<T>> numbers) {
    static_assert(std::is_convertible<T, double>::value, "Matrix::create requires numbers can be converted to double.");

    if (numbers.begin() == numbers.end() || numbers.begin()->begin() == numbers.begin()->end()) {
      throw std::invalid_argument(CURRENT_LINE +
                                  " create: empty std::initializer_list cannot be used to create a Matrix.");
    }

    size_t num_row = 0;
    size_t num_col = 0;
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter, ++num_row)
      ;
    if (numbers.begin() != numbers.end()) {
      for (auto iter = numbers.begin()->begin(); iter != numbers.begin()->end(); ++iter, ++num_col)
        ;
    }

    if (num_row == 0 || num_col == 0) {
      throw std::invalid_argument(CURRENT_LINE + " create: invalid initializer_list");
    }

    Matrix matrix(num_row, num_col);

    int i = 0;
    for (auto row_iter = numbers.begin(); i < num_row && row_iter; ++i, ++row_iter) {
      int j = 0;
      for (auto col_iter = row_iter->begin(); j < num_col && col_iter; ++j, ++col_iter) {
        matrix._data[i * num_col + j] = *col_iter;
      }
    }

    return matrix;
  }

  Matrix operator-();
  Matrix operator-() const;

  static Matrix create(size_t num_row, size_t num_col);
  static Matrix unchecked_create(size_t num_row, size_t num_col);
  static Matrix unchecked_create(int num_row, int num_col, std::initializer_list<std::initializer_list<double>> numbers);
  static Matrix id(size_t num_rows);
  static Matrix zero(size_t num_row, size_t num_col);
  double* operator[](size_t row);
  const double* operator[](size_t row) const;
  double at(size_t row, size_t col) const;
  bool is_square() const;
  bool multiply_inplace(const Matrix& b);
  bool multiply_inplace(const Tuple& b);
  bool multiply_to_tuple(const Tuple& b, Tuple& out_product) const;
  Matrix transpose() const;
  void transpose_inplace();
  double determinant() const;
  bool is_invertible() const;
  Matrix submatrix(size_t row, size_t col) const;
  double minor(size_t row, size_t col) const;
  double cofactor(size_t row, size_t col) const;
  Matrix inverse() const;
  size_t rows() const;
  size_t cols() const;

 private:
  Matrix() = default;
  Matrix(size_t num_row, size_t num_col)
      : _num_row{num_row}, _num_col{num_col} {
    if (_mem_pool == nullptr) {
      _mem_pool = std::make_unique<MemoryPool<double>>(200, 16);
    }

    _assigned_mem = _mem_pool->alloc();
    _data = _assigned_mem->get();
  }

  MemoryChunk<double>* _assigned_mem;
  double* _data;
  size_t _num_row;
  size_t _num_col;

  static std::unique_ptr<MemoryPool<double>> _mem_pool;
};

bool operator==(const Matrix& a, const Matrix& b);
bool operator!=(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);
Tuple operator*(const Matrix& a, const Tuple& b);
Point operator*(const Matrix& a, const Point& b);
Vector operator*(const Matrix& a, const Vector& b);
std::ostream& operator<<(std::ostream& out, const Matrix& m);
}  // namespace RayTracer

