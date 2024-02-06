#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      if (matrix_[i][j] - other.matrix_[i][j] > EPS) return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the number "
        "of rows in the second matrix");

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the number "
        "of rows in the second matrix");

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the rows in "
        "second matrix");

  S21Matrix resultMatrix(rows_, other.cols_);

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < other.cols_; ++j) {
      for (auto k = 0; k < cols_; ++k) {
        resultMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = resultMatrix;
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix resultMatrix(cols_, rows_);

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[i][j] = matrix_[j][i];
    }
  }

  return resultMatrix;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");

  if (rows_ == 1) return matrix_[0][0];

  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];

  double result = 0.;
  for (auto i = 0; i < rows_; ++i) {
    S21Matrix tmp(rows_ - 1, cols_ - 1);
    for (auto j = 1; j < rows_; ++j) {
      for (auto k = 0; k < cols_; ++k) {
        if (k < i)
          tmp.matrix_[j - 1][k] = matrix_[j][k];
        else if (k > i)
          tmp.matrix_[j - 1][k - 1] = matrix_[j][k];
      }
    }
    result += matrix_[0][i] * pow(-1, i) * tmp.Determinant();
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");

  S21Matrix resultMatrix(rows_, cols_);

  if (rows_ == 1) {
    resultMatrix.matrix_[0][0] = 1;
    return resultMatrix;
  }

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[i][j] =
          ((i + j) % 2 ? -1 : 1) * minorMatrix(i, j).Determinant();
    }
  }

  return resultMatrix;
}

S21Matrix S21Matrix::minorMatrix(int im, int jm) noexcept {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  int mRow = 0;
  int mCol = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == im) continue;
    mCol = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == jm) continue;
      minor.matrix_[mRow][mCol] = matrix_[i][j];
      mCol++;
    }
    mRow++;
  }
  return minor;
}

S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();

  if (!determinant) throw std::invalid_argument("Matrix determinant is 0");

  return CalcComplements().Transpose() * (1. / determinant);
}
