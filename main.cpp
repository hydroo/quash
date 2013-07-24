#include <QDebug>

#include "complex.hpp"
#include "complexvector.hpp"
#include "complexmatrix.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    ComplexMatrix m(ComplexMatrix::fromString(
            "[1, -i, i]"
            "[0,  1, 0]"
            "[i, -i, 1]"));
    ComplexMatrix n(ComplexMatrix::fromString(
            "[1, 0, 0]"
            "[0, 1, 0]"
            "[0, 0, 1]"));

    ComplexMatrix h(ComplexMatrix::fromString(
            "[0.7071067811865475, 0.7071067811865475]"
            "[0.7071067811865475, -0.7071067811865475]"));

    qDebug() << "";
    qDebug() << m << '\n' << n;
    qDebug() << "+   " << h.transpose().conjugate();
    qDebug() << "unit" << ComplexMatrix::mul(h, h.transpose().conjugate());

    return 0;
}

