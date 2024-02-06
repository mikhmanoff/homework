#include "s21_matrix_oop.h"

// Перегрузка оператора присваивания для копирования
S21Matrix& S21Matrix::operator=(S21Matrix const& other) {
  if (this != &other) {
    S21Matrix tmp(other);  // Создание временной копии
    swap(tmp);  // Обмен текущего объекта с временным
  }
  return *this;
}

// Перегрузка оператора присваивания для перемещения
S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    S21Matrix tmp(other);  // Создание временной копии
    swap(tmp);  // Обмен текущего объекта с временным
  }
  return *this;
}

// Перегрузка оператора сложения матриц
S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix res(*this);  // Создание копии текущей матрицы
  res.SumMatrix(other);  // Сложение с другой матрицей
  return res;            // Возврат результата
}

// Перегрузка оператора вычитания матриц
S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix res(*this);  // Создание копии текущей матрицы
  res.SubMatrix(other);  // Вычитание другой матрицы
  return res;            // Возврат результата
}

// Перегрузка оператора сложения с присваиванием
S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);  // Сложение с другой матрицей
  return *this;
}

// Перегрузка оператора вычитания с присваиванием
S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);  // Вычитание другой матрицы
  return *this;
}

// Перегрузка оператора умножения матриц
S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix res(*this);  // Создание копии текущей матрицы
  res.MulMatrix(other);  // Умножение на другую матрицу
  return res;            // Возврат результата
}

// Перегрузка оператора умножения матрицы на число
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res(*this);  // Создание копии текущей матрицы
  res.MulNumber(num);  // Умножение на число
  return res;          // Возврат результата
}

// Перегрузка оператора умножения с присваиванием матрицы
S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);  // Умножение на другую матрицу
  return *this;
}

// Перегрузка оператора умножения с присваиванием на число
S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);  // Умножение на число
  return *this;
}

// Перегрузка оператора сравнения матриц на равенство
bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);  // Сравнение матриц на равенство
}

// Перегрузка оператора доступа к элементу матрицы по индексам
double& S21Matrix::operator()(int i, int j) const {
  return getElem(i, j);  // Получение ссылки на элемент матрицы
}
