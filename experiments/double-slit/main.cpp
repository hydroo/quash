// book pages 92-95

#include <cmath>

#include <QDebug>

#include "complex.hpp"
#include "complexmatrix.hpp"
#include "debug.hpp"
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
    Complex_set(m.at(1, 0), Complex(1 / sqrt(2)));
    Complex_set(m.at(2, 0), Complex(1 / sqrt(2)));

    Complex_set(m.at(3, 1), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(m.at(4, 1), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(m.at(5, 1), Complex_div(Complex_fromString(" 1-i"), Real(sqrt(6))));

    Complex_set(m.at(5, 2), Complex_div(Complex_fromString("-1+i"), Real(sqrt(6))));
    Complex_set(m.at(6, 2), Complex_div(Complex_fromString("-1-i"), Real(sqrt(6))));
    Complex_set(m.at(7, 2), Complex_div(Complex_fromString(" 1-i"), Real(sqrt(6))));

    State s(ComplexVector_fromString("[1,0,0,0,   0,0,0,0]"));

    State s1(ComplexMatrix_mul(m, s));
    State s2(ComplexMatrix_mul(m, s1));
    State s2probs(State_probabilities(s2));

    qDebug() << "system       " << "\n" << m;
    qDebug() << "start        " << s;
    qDebug() << "round 2      " << ComplexVector_toString(s2, 3);
    qDebug() << "round 2 probs" << ComplexVector_toString(s2probs, 3);

    ASSERT(ComplexVector_isEqual(s2probs, ComplexVector_fromString("[0, 0, 0, 0.25, 0.25, 0, 0.25, 0.25]")));

    return 0;
}

