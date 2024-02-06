#include "s21_matrix_oop.h"

// Проверка на равенство матриц
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_)
    return false;  // Если размеры матриц не совпадают, возвращаем false

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      // Сравниваем каждый элемент матрицы с соответствующим элементом другой
      // матрицы с учетом погрешности EPS
      if (matrix_[i][j] - other.matrix_[i][j] > EPS) return false;
    }
  }

  return true;  // Если все элементы совпадают с учетом погрешности, возвращаем
                // true
}

// Сложение матриц
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the number "
        "of rows in the second matrix");  // Проверка на соответствие размеров
                                          // матриц для сложения

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] +=
          other.matrix_[i][j];  // Сложение соответствующих элементов матриц
    }
  }
}

// Вычитание матриц
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the number "
        "of rows in the second matrix");  // Проверка на соответствие размеров
                                          // матриц для вычитания

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] -=
          other.matrix_[i][j];  // Вычитание соответствующих элементов матриц
    }
  }
}

// Умножение матриц
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "The number of columns in the first matrix is not equal to the rows in "
        "second matrix");  // Проверка на соответствие размеров матриц для
                           // умножения

  S21Matrix resultMatrix(rows_,
                         other.cols_);  // Создание матрицы для результата

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < other.cols_; ++j) {
      for (auto k = 0; k < cols_; ++k) {
        resultMatrix.matrix_[i][j] +=
            matrix_[i][k] *
            other.matrix_[k][j];  // Вычисление элементов результирующей матрицы
      }
    }
  }

  *this = resultMatrix;  // Присвоение результата текущей матрице
}

// Умножение матрицы на число
void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;  // Умножение каждого элемента матрицы на число
    }
  }
}

// Транспонирование матрицы
S21Matrix S21Matrix::Transpose() {
  S21Matrix resultMatrix(cols_, rows_);  // Создание матрицы для результата

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[i][j] =
          matrix_[j][i];  // Заполнение результата транспонированными элементами
    }
  }

  return resultMatrix;  // Возврат результата
}

// Вычисление определителя матрицы
double S21Matrix::Determinant() {
  if (rows_ != cols_)
    throw std::invalid_argument(
        "The matrix is not square");  // Проверка на квадратность матрицы

  if (rows_ == 1)
    return matrix_[0][0];  // Для матрицы 1x1 определитель равен её
                           // единственному элементу

  if (rows_ == 2)
    return matrix_[0][0] * matrix_[1][1] -
           matrix_[0][1] *
               matrix_[1][0];  // Формула для определителя матрицы 2x2

  double result = 0.;
  for (auto i = 0; i < rows_; ++i) {
    S21Matrix tmp(rows_ - 1, cols_ - 1);  // Создание матрицы для минора
    for (auto j = 1; j < rows_; ++j) {
      for (auto k = 0; k < cols_; ++k) {
        if (k < i)
          tmp.matrix_[j - 1][k] = matrix_[j][k];
        else if (k > i)
          tmp.matrix_[j - 1][k - 1] = matrix_[j][k];
      }
    }
    result += matrix_[0][i] * pow(-1, i) *
              tmp.Determinant();  // Рекурсивное вычисление определителя
  }

  return result;  // Возврат результата
}

// Вычисление матрицы дополнений
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_)
    throw std::invalid_argument(
        "The matrix is not square");  // Проверка на квадратность матрицы

  S21Matrix resultMatrix(rows_, cols_);  // Создание матрицы для результата

  if (rows_ == 1) {
    resultMatrix.matrix_[0][0] = 1;  // Для матрицы 1x1 её дополнение равно 1
    return resultMatrix;
  }

  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      resultMatrix.matrix_[i][j] =
          ((i + j) % 2 ? -1 : 1) *
          minorMatrix(i, j).Determinant();  // Заполнение матрицы дополнений
    }
  }

  return resultMatrix;  // Возврат результата
}

// Вычисление минора матрицы
S21Matrix S21Matrix::minorMatrix(int im, int jm) noexcept {
  S21Matrix minor(rows_ - 1, cols_ - 1);  // Создание матрицы для минора
  int mRow = 0;
  int mCol = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == im) continue;
    mCol = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == jm) continue;
      minor.matrix_[mRow][mCol] = matrix_[i][j];  // Заполнение минора
      mCol++;
    }
    mRow++;
  }
  return minor;  // Возврат минора
}

// Вычисление обратной матрицы
S21Matrix S21Matrix::InverseMatrix() {
  double determinant = Determinant();  // Вычисление определителя

  if (!determinant)
    throw std::invalid_argument(
        "Matrix determinant is 0");  // Проверка на нулевой определитель

  return CalcComplements().Transpose() *
         (1. / determinant);  // Вычисление обратной матрицы
}
