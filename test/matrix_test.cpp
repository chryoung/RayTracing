#include "math/matrix.h"

#include <gtest/gtest.h>

#include <memory>

#include "math/tuple.h"

using namespace RayTracer;

TEST(Matrix, WhenCreateAMatrixExpectAMatrix) {
  auto m = Matrix::create(2, 3);
  EXPECT_EQ(2, m.rows());
  EXPECT_EQ(3, m.cols());
}

TEST(Matrix, WhenCreateMatrixWithZeroRowColExpectThrowException) {
  EXPECT_THROW(Matrix::create(0, 1), std::invalid_argument) << "Creating a Matrix with 0 row should throw exception.";
  EXPECT_THROW(Matrix::create(1, 0), std::invalid_argument) << "Creating a Matrix with 0 col should throw exception.";
  EXPECT_THROW(Matrix::create(0, 0), std::invalid_argument)
      << "Creating a Matrix with 0 row and 0 col should throw exception.";
}

TEST(Matrix, WhenCreateAMatrixWithRowsWithDifferentNumbersOfColExpectThrowException) {
  EXPECT_THROW(Matrix::create({{1}, {1, 2}}), std::invalid_argument);
  EXPECT_THROW(Matrix::create({{1, 2}, {1}}), std::invalid_argument);
}

TEST(Matrix, WhenCreateWithEmptyListExpectException) {
  EXPECT_THROW(Matrix::create<double>({{}}), std::invalid_argument);
  EXPECT_THROW(Matrix::create<double>({{1}, {}}), std::invalid_argument);
  EXPECT_THROW(Matrix::create<double>({{}, {1}}), std::invalid_argument);
}

TEST(Matrix, WhenCreateAMatrixPointerExpectPointerToMatrix) {
  std::unique_ptr<Matrix> m(new Matrix(Matrix::create({{2, 3}, {3, 4}, {4, 5}})));
  EXPECT_NE(nullptr, m);
  EXPECT_EQ(3, m->rows());
  EXPECT_EQ(2, m->cols());
  EXPECT_EQ(3, (*m)[1][0]);
  EXPECT_EQ(4, (*m)[1][1]);
}

TEST(Matrix, WhenMatrixIndexOverflowsExpectThrowException) {
  auto m = Matrix::create({{1}});
  EXPECT_THROW(m.at(-1, 0), std::out_of_range);
  EXPECT_THROW(m.at(1, 0), std::out_of_range);
  EXPECT_THROW(m.at(0, 1), std::out_of_range);
  EXPECT_THROW(m.at(0, -1), std::out_of_range);
}

TEST(Matrix, WhenCreate4x4MatrixExpect4x4Matrix) {
  Matrix m = Matrix::create<double>({
      {1, 2, 3, 4},
      {5.5, 6.5, 7.5, 8.5},
      {9, 10, 11, 12},
      {13.5, 14.5, 15.5, 16.5},
  });

  EXPECT_DOUBLE_EQ(1, m[0][0]);
  EXPECT_DOUBLE_EQ(4, m[0][3]);
  EXPECT_DOUBLE_EQ(5.5, m[1][0]);
  EXPECT_DOUBLE_EQ(7.5, m[1][2]);
  EXPECT_DOUBLE_EQ(11, m[2][2]);
  EXPECT_DOUBLE_EQ(13.5, m[3][0]);
  EXPECT_DOUBLE_EQ(15.5, m[3][2]);
}

TEST(Matrix, WhenCreate2x2MatrixExpect2x2Matrix) {
  Matrix m = Matrix::create({
      {-3, 5},
      {1, -2},
  });

  EXPECT_DOUBLE_EQ(-3, m[0][0]);
  EXPECT_DOUBLE_EQ(5, m[0][1]);
  EXPECT_DOUBLE_EQ(1, m[1][0]);
  EXPECT_DOUBLE_EQ(-2, m[1][1]);
}

TEST(Matrix, WhenCreate3x3MatrixExpect3x3Matrix) {
  Matrix m = Matrix::create({
      {-3, 5, 0},
      {1, -2, -7},
      {0, 1, 1},
  });

  EXPECT_DOUBLE_EQ(-3, m[0][0]);
  EXPECT_DOUBLE_EQ(-2, m[1][1]);
  EXPECT_DOUBLE_EQ(1, m[2][2]);
}

TEST(Matrix, WhenMatricesAreEqualExpectOperatorEqualReturnTrue) {
  Matrix a = Matrix::create({
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 8, 7, 6},
      {5, 4, 3, 2},
  });

  Matrix b = Matrix::create({
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 8, 7, 6},
      {5, 4, 3, 2},
  });

  EXPECT_TRUE(a == a);
  EXPECT_TRUE(a == b);
  EXPECT_TRUE(b == a);
  EXPECT_EQ(a, b);
}

TEST(Matrix, WhenMatricesAreNotEqualExpectOperatorNotEqualReturnTrue) {
  Matrix a = Matrix::create({
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 8, 7, 6},
      {5, 4, 3, 2},
  });

  Matrix b = Matrix::create({
      {2, 3, 4, 5},
      {6, 7, 8, 9},
      {8, 7, 6, 5},
      {4, 3, 2, 1},
  });

  EXPECT_TRUE(a != b);
  EXPECT_TRUE(b != a);
  EXPECT_NE(a, b);
}

TEST(Matrix, WhenMatrixMultiplyMatrixExpectCorrectProduct) {
  Matrix a = Matrix::create({
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 8, 7, 6},
      {5, 4, 3, 2},
  });

  Matrix b = Matrix::create({
      {-2, 1, 2, 3},
      {3, 2, 1, -1},
      {4, 3, 6, 5},
      {1, 2, 7, 8},
  });

  auto c = a * b;
  EXPECT_TRUE(a.multiply_inplace(b));

  Matrix truth = Matrix::create({
      {20, 22, 50, 48},
      {44, 54, 114, 108},
      {40, 58, 110, 102},
      {16, 26, 46, 42},
  });

  EXPECT_EQ(truth, c);
  EXPECT_EQ(truth, a);
}

TEST(Matrix, WhenAMatrixMultipliedByATupleExpectATuple) {
  Matrix a = Matrix::create({
      {1, 2, 3, 4},
      {2, 4, 4, 2},
      {8, 6, 4, 1},
      {0, 0, 0, 1},
  });

  Tuple b(1, 2, 3, 1);
  Tuple c;
  EXPECT_TRUE(a.multiply_to_tuple(b, c));
  EXPECT_EQ(Tuple(18, 24, 33, 1), c);
}

TEST(Matrix, WhenMultiplyAMatrixByTheIdentityMatrixExpectItself) {
  Matrix a = Matrix::create({
      {0, 1, 2, 4},
      {1, 2, 4, 8},
      {2, 4, 8, 16},
      {4, 8, 16, 32},
  });

  Matrix b = a * Matrix::id(a.rows());
  EXPECT_EQ(a, b);
}

TEST(Matrix, WhenTransposeAMatrixExpectTranspose) {
  Matrix a = Matrix::create({
      {0, 9, 3, 0},
      {9, 8, 0, 8},
      {1, 8, 5, 3},
      {0, 0, 5, 8},
  });

  Matrix ta = Matrix::create({
      {0, 9, 1, 0},
      {9, 8, 8, 0},
      {3, 0, 5, 5},
      {0, 8, 3, 8},
  });

  EXPECT_EQ(ta, a.transpose());
}

TEST(Matrix, WhenTransposeAnIdentityMatrixExpectAnIdentityMatrix) {
  Matrix a = Matrix::id(4);
  EXPECT_EQ(a, a.transpose());
}

TEST(Matrix, WhenGetDeterminantOf2x2MatrixExpectDeterminant) {
  Matrix a = Matrix::create({
      {1, 5},
      {-3, 2},
  });

  EXPECT_DOUBLE_EQ(17, a.determinant());
}

TEST(Matrix, WhenGetSubMatrixOf3x3MatrixExpectMatrix2x2) {
  Matrix a = Matrix::create({
      {1, 5, 0},
      {-3, 2, 7},
      {0, 6, -3},
  });

  Matrix sub_0_2 = Matrix::create({
      {-3, 2},
      {0, 6},
  });

  Matrix sub_1_1 = Matrix::create({
      {1, 0},
      {0, -3},
  });

  Matrix sub_2_2 = Matrix::create({
      {1, 5},
      {-3, 2},
  });

  EXPECT_EQ(sub_0_2, a.submatrix(0, 2));
  EXPECT_EQ(sub_1_1, a.submatrix(1, 1));
  EXPECT_EQ(sub_2_2, a.submatrix(2, 2));
}

TEST(Matrix, WhenGetSubMatrixOf4x4MatrixExpectMatrix3x3) {
  Matrix a = Matrix::create({
      {-6, 1, 1, 6},
      {-8, 5, 8, 6},
      {-1, 0, 8, 2},
      {-7, 1, -1, 1},
  });

  Matrix sub_2_1 = Matrix::create({
      {-6, 1, 6},
      {-8, 8, 6},
      {-7, -1, 1},
  });

  EXPECT_EQ(sub_2_1, a.submatrix(2, 1));
}

TEST(Matrix, WhenGetMinorOf3x3MatrixExpectMinor) {
  Matrix a = Matrix::create({
      {3, 5, 0},
      {2, -1, -7},
      {6, -1, 5},
  });

  EXPECT_DOUBLE_EQ(25, a.minor(1, 0));
}

TEST(Matrix, WhenGetCofactorOf3x3MatrixExpectCofactor) {
  Matrix a = Matrix::create({{3, 5, 0}, {2, -1, -7}, {6, -1, 5}});

  EXPECT_DOUBLE_EQ(-12, a.minor(0, 0));
  EXPECT_DOUBLE_EQ(-12, a.cofactor(0, 0));
  EXPECT_DOUBLE_EQ(25, a.minor(1, 0));
  EXPECT_DOUBLE_EQ(-25, a.cofactor(1, 0));
}

TEST(Matrix, WhenGetDeterminantOf3x3MatrixExpectDeterminant) {
  Matrix a = Matrix::create({
      {1, 2, 6},
      {-5, 8, -4},
      {2, 6, 4},
  });

  EXPECT_DOUBLE_EQ(56, a.cofactor(0, 0));
  EXPECT_DOUBLE_EQ(12, a.cofactor(0, 1));
  EXPECT_DOUBLE_EQ(-46, a.cofactor(0, 2));
  EXPECT_DOUBLE_EQ(-196, a.determinant());
}

TEST(Matrix, WhenGetDeterminantOf4x4MatrixExpectDeterminant) {
  Matrix a = Matrix::create({
      {-2, -8, 3, 5},
      {-3, 1, 7, 3},
      {1, 2, -9, 6},
      {-6, 7, 7, -9},
  });

  EXPECT_DOUBLE_EQ(690, a.cofactor(0, 0));
  EXPECT_DOUBLE_EQ(447, a.cofactor(0, 1));
  EXPECT_DOUBLE_EQ(210, a.cofactor(0, 2));
  EXPECT_DOUBLE_EQ(51, a.cofactor(0, 3));
  EXPECT_DOUBLE_EQ(-4071, a.determinant());
}

TEST(Matrix, WhenGetInverseOf4x4MatrixExpectInverseMatrix1) {
  Matrix a = Matrix::create({
      {-5, 2, 6, -8},
      {1, -5, 1, 8},
      {7, 7, -6, -7},
      {1, -3, 7, 4},
  });

  EXPECT_TRUE(a.is_invertible());
  Matrix b = a.inverse();
  EXPECT_DOUBLE_EQ(532, a.determinant());
  EXPECT_DOUBLE_EQ(-160, a.cofactor(2, 3));
  EXPECT_DOUBLE_EQ(-160.0 / 532, b[3][2]);
  EXPECT_DOUBLE_EQ(105, a.cofactor(3, 2));
  EXPECT_DOUBLE_EQ(105.0 / 532, b[2][3]);

  Matrix i = Matrix::create({{0.21804511, 0.45112782, 0.2406015, -0.04511278},
                             {-0.80827068, -1.45676692, -0.44360902, 0.52067669},
                             {-0.07894737, -0.22368421, -0.05263158, 0.19736842},
                             {-0.52255639, -0.81390977, -0.30075188, 0.30639098}});

  EXPECT_EQ(i, b);
}

TEST(Matrix, WhenGetInverseOf4x4MatrixExpectInverseMatrix2) {
  Matrix a = Matrix::create({
      {8, -5, 9, 2},
      {7, 5, 6, 1},
      {-6, 0, 9, 6},
      {-3, 0, -9, -4},
  });

  Matrix i = Matrix::create({{-0.15384615, -0.15384615, -0.28205128, -0.53846154},
                             {-0.07692308, 0.12307692, 0.02564103, 0.03076923},
                             {0.35897436, 0.35897436, 0.43589744, 0.92307692},
                             {-0.69230769, -0.69230769, -0.76923077, -1.92307692}});

  EXPECT_EQ(i, a.inverse());
}

TEST(Matrix, WhenGetInverseOf4x4MatrixExpectInverseMatrix3) {
  Matrix a = Matrix::create({
      {9, 3, 0, 9},
      {-5, -2, -6, -3},
      {-4, 9, 6, 4},
      {-7, 6, 6, 2},
  });

  Matrix i = Matrix::create({{-0.04074074, -0.07777778, 0.14444444, -0.22222222},
                             {-0.07777778, 0.03333333, 0.36666667, -0.33333333},
                             {-0.02901235, -0.1462963, -0.10925926, 0.12962963},
                             {0.17777778, 0.06666667, -0.26666667, 0.33333333}});

  EXPECT_EQ(i, a.inverse());
}

TEST(Matrix, WhenMultiplyAProductByItsInverseExpectAFactor) {
  Matrix a = Matrix::create({
      {3, -9, 7, 3},
      {3, -8, 2, -9},
      {-4, 4, 4, 1},
      {-6, 5, -1, 1},
  });

  Matrix b = Matrix::create({
      {8, 2, 2, 2},
      {3, -1, 7, 0},
      {7, 0, 5, 4},
      {6, -2, 0, 5},
  });

  auto c = a * b;
  EXPECT_EQ(a, c * b.inverse());
}