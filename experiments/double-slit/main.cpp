// book pages 92-95

#include <cmath>

#include <QDebug>

#include "complex.hpp"
#include "complexvector.hpp"
#include "complexmatrix.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    ComplexMatrix m(ComplexMatrix::fromString(
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 1,   0, 0, 0, 0]"
            "                          "
            "[0, 0, 0, 0,   1, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 1, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 1, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 1]"));
    Complex_set(&m.at(1, 0), Complex_fromReal(Real_fromDouble(1 / sqrt(2))));
    Complex_set(&m.at(2, 0), Complex_fromReal(Real_fromDouble(1 / sqrt(2))));

    Complex_set(&m.at(3, 1), Complex_div(Complex_fromString("-1+i"), Real_fromDouble(sqrt(6))));
    Complex_set(&m.at(4, 1), Complex_div(Complex_fromString("-1+i"), Real_fromDouble(sqrt(6))));
    Complex_set(&m.at(5, 1), Complex_div(Complex_fromString(" 1-i"), Real_fromDouble(sqrt(6))));

    Complex_set(&m.at(5, 2), Complex_div(Complex_fromString("-1+i"), Real_fromDouble(sqrt(6))));
    Complex_set(&m.at(6, 2), Complex_div(Complex_fromString("-1-i"), Real_fromDouble(sqrt(6))));
    Complex_set(&m.at(7, 2), Complex_div(Complex_fromString(" 1-i"), Real_fromDouble(sqrt(6))));

    ComplexVector v(ComplexVector::fromString("[1,0,0,0,   0,0,0,0]"));

    qDebug() << "system       " << "\n" << m;
    qDebug() << "start        " << v;
    qDebug() << "round 1      " << ComplexMatrix::mul(m, v).toString(3);
    qDebug() << "round 2      " << ComplexMatrix::mul(m, ComplexMatrix::mul(m, v)).toString(3);

    return 0;
}

