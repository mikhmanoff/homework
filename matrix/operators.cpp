#include "s21_matrix_oop.h"

S21Matrix& S21Matrix::operator=(S21Matrix const& other) {
  if (this != &other) {
    S21Matrix tmp(other);
    swap(tmp);
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    S21Matrix tmp(other);
    swap(tmp);
  }

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

double& S21Matrix::operator()(int i, int j) const { return getElem(i, j); }
