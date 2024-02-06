#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#define EPS 1e-10  // Задаем погрешность

class S21Matrix {
 private:
  int rows_ = 0;  // Количество строк
  int cols_ = 0;  // Количество столбцов
  double** matrix_ =
      nullptr;  // Указатель на двумерный массив для хранения матрицы
  /* data */
  void freeMemory() noexcept;  // Освобождение памяти

 public:
  // Конструкторы и деструктор
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Конструктор с параметрами
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор перемещения
  ~S21Matrix();                  // Деструктор

  // Функции для работы с матрицей
  void printMatrix() noexcept;  // Вывод матрицы на экран
  void fillMatrix() noexcept;  // Заполнение матрицы с клавиатуры
  void fillMatrix(
      const double val) noexcept;  // Заполнение матрицы заданным значением
  void fillMatrixArr(
      const double* arr) noexcept;  // Заполнение матрицы массивом значений
  void swap(S21Matrix& other) noexcept;  // Обмен содержимым двух матриц
  S21Matrix minorMatrix(int im, int jm) noexcept;  // Получение минора матрицы

  // Операции над матрицами
  bool EqMatrix(const S21Matrix& other) const;  // Проверка на равенство матриц
  void SumMatrix(const S21Matrix& other);  // Сложение матриц
  void SubMatrix(const S21Matrix& other);  // Вычитание матриц
  void MulNumber(const double num);  // Умножение матрицы на число
  void MulMatrix(const S21Matrix& other);  // Умножение матриц
  S21Matrix Transpose();  // Транспонирование матрицы
  S21Matrix CalcComplements();  // Вычисление матрицы дополнений
  double Determinant();  // Вычисление определителя матрицы
  S21Matrix InverseMatrix();  // Вычисление обратной матрицы

  // Перегрузка операторов
  S21Matrix& operator=(
      S21Matrix const& other);  // Оператор присваивания для копирования
  S21Matrix& operator=(
      S21Matrix&& other);  // Оператор присваивания для перемещения
  S21Matrix operator+(
      const S21Matrix& other) const;  // Оператор сложения матриц
  S21Matrix operator-(
      const S21Matrix& other) const;  // Оператор вычитания матриц
  S21Matrix& operator+=(
      const S21Matrix& other);  // Оператор сложения с присваиванием
  S21Matrix& operator-=(
      const S21Matrix& other);  // Оператор вычитания с присваиванием
  S21Matrix operator*(
      const S21Matrix& other) const;  // Оператор умножения матриц
  S21Matrix operator*(
      const double num) const;  // Оператор умножения матрицы на число
  S21Matrix& operator*=(
      const double num);  // Оператор умножения на число с присваиванием
  S21Matrix& operator*=(
      const S21Matrix& other);  // Оператор умножения с присваиванием
  bool operator==(
      const S21Matrix& other) const;  // Оператор сравнения матриц на равенство
  double& operator()(
      int i, int j) const;  // Оператор доступа к элементу матрицы по индексам

  // Геттеры и сеттеры для количества строк и столбцов
  int getRows() const;  // Получение количества строк
  int getCols() const;  // Получение количества столбцов
  void setRows(int rows);  // Установка количества строк
  void setCols(int cols);  // Установка количества столбцов
  double& getElem(int i,
                  int j) const;  // Получение элемента матрицы по индексам
};

#endif  // S21_MATRIX_OOP_H
