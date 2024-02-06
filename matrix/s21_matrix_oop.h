#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#define EPS 1e-10

class S21Matrix {
 private:
  int rows_ = 0;
  int cols_ = 0;
  double** matrix_ = nullptr;
  /* data */
  void freeMemory() noexcept;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  void printMatrix() noexcept;
  void fillMatrix() noexcept;
  void fillMatrix(const double val) noexcept;
  void fillMatrixArr(const double* arr) noexcept;
  void swap(S21Matrix& other) noexcept;
  S21Matrix minorMatrix(int im, int jm) noexcept;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix& operator=(S21Matrix const& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;
  double& operator()(int i, int j) const;

  int getRows() const;
  int getCols() const;
  void setRows(int rows);
  void setCols(int cols);
  double& getElem(int i, int j) const;
};

#endif  // S21_MATRIX_OOP_H