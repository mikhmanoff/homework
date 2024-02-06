#include <algorithm>
#include <iostream>
#include <string>

class BigInteger {
 private:
  static const int SIZE = 40;  // Размер массива
  int digits[SIZE];            // Массив для хранения цифр
  bool negative;  // Флаг отрицательности числа

 public:
  BigInteger() {
    std::fill(digits, digits + SIZE, 0);  // Инициализация массива нулями
    negative = false;  // По умолчанию число не отрицательное
  }

  // Функция для установки значения большого целого числа из строки
  void setFromString(const std::string& number) {
    std::fill(digits, digits + SIZE, 0);  // Очищаем массив
    negative = (number[0] == '-');  // Проверяем отрицательность числа
    int start =
        (negative ? 1 : 0);  // Устанавливаем начальный индекс для чтения цифр
    int end = number.size();  // Определяем конечный индекс
    for (int i = start, j = 0; i < end; ++i, ++j) {
      digits[j] = number[end - 1 - i] -
                  '0';  // Заполняем массив цифрами в обратном порядке
    }
  }

  // Функция для вывода значения большого целого числа
  void print() const {
    if (negative) std::cout << "-";
    bool leadingZeros = true;
    for (int i = SIZE - 1; i >= 0; --i) {
      if (digits[i] != 0) leadingZeros = false;
      if (!leadingZeros) std::cout << digits[i];
    }
    if (leadingZeros) std::cout << "0";  // Выводим "0", если число ноль
    std::cout << std::endl;
  }

  // Функция для сложения больших целых чисел
  BigInteger add(const BigInteger& other) const {
    BigInteger result;
    int carry = 0;
    for (int i = 0; i < SIZE; ++i) {
      int sum = digits[i] + other.digits[i] + carry;
      result.digits[i] = sum % 10;
      carry = sum / 10;
    }
    result.negative =
        (negative && other.negative);  // Проверяем знак результата
    return result;
  }

  // Функция для вычитания больших целых чисел
  BigInteger subtract(const BigInteger& other) const {
    BigInteger result;
    int borrow = 0;
    for (int i = 0; i < SIZE; ++i) {
      int diff = digits[i] - other.digits[i] - borrow;
      if (diff < 0) {
        diff += 10;
        borrow = 1;
      } else {
        borrow = 0;
      }
      result.digits[i] = diff;
    }
    result.negative =
        (negative && !other.negative);  // Проверяем знак результата
    return result;
  }

  // Функция для сравнения больших целых чисел
  int compare(const BigInteger& other) const {
    if (negative && !other.negative)
      return -1;  // Если текущее число отрицательное, а другое положительное,
                  // то текущее меньше
    if (!negative && other.negative)
      return 1;  // Если текущее число положительное, а другое отрицательное, то
                 // текущее больше

    for (int i = SIZE - 1; i >= 0; --i) {
      if (digits[i] < other.digits[i])
        return -1;  // Если текущая цифра меньше, текущее число меньше
      if (digits[i] > other.digits[i])
        return 1;  // Если текущая цифра больше, текущее число больше
    }
    return 0;  // Числа равны
  }

  // Функция для умножения больших целых чисел
  BigInteger multiply(const BigInteger& other) const {
    BigInteger result;
    BigInteger temp;
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        temp.digits[j] = digits[i] * other.digits[j];
      }
      // Добавляем временный результат к общему результату с учетом сдвига
      for (int k = 0; k < i; ++k) {
        temp.shiftLeft();
      }
      result = result.add(temp);
    }
    result.negative =
        (negative && other.negative);  // Проверяем знак результата
    return result;
  }

  // Функция для деления больших целых чисел
  BigInteger divide(const BigInteger& other) const {
    BigInteger quotient;
    BigInteger remainder(*this);
    while (remainder.compare(other) >= 0) {
      BigInteger temp = other;
      int count = 0;
      while (remainder.compare(temp) >= 0) {
        remainder = remainder.subtract(temp);
        quotient = quotient.add(BigInteger("1").shiftLeft(count));
        temp.shiftLeft(1);
        count++;
      }
    }
    quotient.negative =
        (negative && other.negative);  // Проверяем знак результата
    return quotient;
  }

  // Функция для сдвига числа на один разряд влево
  void shiftLeft(int places = 1) {
    for (int i = SIZE - 1; i >= places; --i) {
      digits[i] = digits[i - places];
    }
    for (int i = 0; i < places; ++i) {
      digits[i] = 0;
    }
  }
};

int main() {
  BigInteger num1, num2;
  std::string strNum1, strNum2;

  // Ввод чисел
  std::cout << "Введите первое большое целое число: ";
  std::cin >> strNum1;
  std::cout << "Введите второе большое целое число: ";
  std::cin >> strNum2;

  // Установка значений чисел
  num1.setFromString(strNum1);
  num2.setFromString(strNum2);

  // Вывод чисел
  std::cout << "Первое число: ";
  num1.print();
  std::cout << "Второе число: ";
  num2.print();

  // Сложение
  std::cout << "Сумма: ";
  num1.add(num2).print();

  // Вычитание
  std::cout << "Разность: ";
  num1.subtract(num2).print();

  // Умножение
  std::cout << "Произведение: ";
  num1.multiply(num2).print();

  // Деление
  std::cout << "Частное: ";
  num1.divide(num2).print();

  return 0;
}
