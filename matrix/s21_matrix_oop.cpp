#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(2), cols_(2), matrix_(new double*[rows_]) {
  for (auto i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    std::fill(matrix_[i], matrix_[i] + cols_, 0);
  }
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) throw std::invalid_argument("Zero matrix");

  matrix_ = new double*[rows_];
  for (auto i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    std::fill(matrix_[i], matrix_[i] + cols_, 0);
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  if (rows_ <= 0 || cols_ <= 0) throw std::invalid_argument("Zero matrix");

  matrix_ = new double*[rows_];
  for (auto i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
    std::fill(matrix_[i], matrix_[i] + cols_, 0);
  }

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { freeMemory(); }

void S21Matrix::freeMemory() noexcept {
  for (auto i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }

  delete[] matrix_;
}

void S21Matrix::printMatrix() noexcept {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void S21Matrix::fillMatrix() noexcept {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      std::cin >> matrix_[i][j];
    }
  }
}

void S21Matrix::fillMatrix(const double val) noexcept {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = val;
    }
  }
}

void S21Matrix::fillMatrixArr(const double* arr) noexcept {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = arr[i * cols_ + j];
    }
  }
}

void S21Matrix::swap(S21Matrix& other) noexcept {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

int S21Matrix::getRows() const { return rows_; }

int S21Matrix::getCols() const { return cols_; }

void S21Matrix::setRows(int rows) {
  if (rows <= 0)
    throw std::invalid_argument("The number of rows must be greater than zero");
  S21Matrix result(rows, cols_);
  result.fillMatrix(0);
  for (int i = 0; i < std::min(rows_, rows); i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}

void S21Matrix::setCols(int cols) {
  if (cols <= 0)
    throw std::invalid_argument("The number of cols must be greater than zero");
  S21Matrix result(rows_, cols);
  result.fillMatrix(0);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < std::min(cols_, cols); j++) {
      result.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = result;
}

double& S21Matrix::getElem(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::out_of_range("Index out of range");
  }

  return matrix_[i][j];
}
