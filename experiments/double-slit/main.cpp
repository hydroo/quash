// book pages 92-95

#include <cmath>

#include <QDebug>

#include "complex.hpp"
#include "complexmatrix.hpp"
#include "state.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    ComplexMatrix m(ComplexMatrix_fromString(
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 0]"
            "[0, 0, 0, 1,   0, 0, 0, 0]"
            "                          "
            "[0, 0, 0, 0,   1, 0, 0, 0]"
            "[0, 0, 0, 0,   0, 1, 0, 0]"
            "[0, 0, 0, 0,   0, 0, 1, 0]"
            "[0, 0, 0, 0,   0, 0, 0, 1]"));
    Complex_set(ComplexMatrix_at(&m, 1, 0), Complex(1 / sqrt(2)));
    Complex_set(ComplexMatrix_at(&m, 2, 0), Complex(1 / sqrt(2)));

    Complex_set(ComplexMatrix_at(&m, 3, 1), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(ComplexMatrix_at(&m, 4, 1), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(ComplexMatrix_at(&m, 5, 1), Complex_div(Complex_fromString(" 1-i"), Real(sqrt(6))));

    Complex_set(ComplexMatrix_at(&m, 5, 2), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(ComplexMatrix_at(&m, 6, 2), Complex_div(Complex_fromString("-1-i"), Real(sqrt(6))));
    Complex_set(ComplexMatrix_at(&m, 7, 2), Complex_div(Complex_fromString(" 1-i"), Real(sqrt(6))));

    State s(ComplexVector_fromString("[1,0,0,0,   0,0,0,0]"));

    qDebug() << "system       " << "\n" << m;
    qDebug() << "start        " << s;
    qDebug() << "round 1      " << ComplexVector_toString(ComplexMatrix_mul(m, s), 3);
    qDebug() << "round 2      " << ComplexVector_toString(ComplexMatrix_mul(m, ComplexMatrix_mul(m, s)), 3);
    qDebug() << "round 2 probs" << ComplexVector_toString(State_probabilities(ComplexMatrix_mul(m, ComplexMatrix_mul(m, s))), 3);

    return 0;
}

