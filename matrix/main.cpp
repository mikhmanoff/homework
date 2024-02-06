// #include "mySpace.h"
#include "s21_matrix_oop.h"

using namespace std;

int main() {
  // S21Matrix ppp(10, 20);
  // S21Matrix qqq(move(ppp));
  // qqq.printMatrix();

  // ppp.fillMatrix();
  // cout << fixed;
  // cout.precision(2);

  // ppp.CalcComplements().Transpose().printMatrix();

  // try {
  //     // ppp.InverseMatrix().printMatrix();
  //     ppp = ppp;
  //     // const double test = ppp(0, 0);
  //     // cout << test << endl;
  // } catch (std::exception& e) {
  //     cout << e.what() << endl;
  // }
  // cout << ppp.Determinant() << endl;
  S21Matrix ppp(3, 3);
  ppp.fillMatrix(3);
  ppp.setCols(2);
  ppp.setRows(10);
  ppp.printMatrix();
  // S21Matrix qqq(3, 3);
  // qqq.fillMatrix(-2);
  // ppp = move(qqq);
  // cout << ppp(0, 0) << endl;

  // try {
  //     ppp += qqq;
  // } catch (std::invalid_argument& e) {
  //     std::cout << e.what() << std::endl;
  // }
  // ppp = qqq;
  // S21Matrix rrr;
  // rrr = ppp - qqq;
  // std::cout << ppp.getCols() << std::endl;
  // rrr.printMatrix();
  // ppp.printMatrix();
  // ppp = qqq;
  // ppp.printMatrix();
  // qqq.printMatrix();
  // mySpace::showInfo();
  // std::cout << (ppp == qqq) << std::endl;
  // const double p = ppp(0, 0);
  // std::cout << p << std::endl;

  // qqq.printMatrix();

  return 0;
}