#include <QDebug>

#include "complex.hpp"
#include "complexvector.hpp"
#include "complexmatrix.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    ComplexMatrix m(ComplexMatrix_fromString(
            "[1, -i, i]"
            "[0,  1, 0]"
            "[i, -i, 1]"));
    ComplexMatrix n(ComplexMatrix_fromString(
            "[1, 0, 0]"
            "[0, 1, 0]"
            "[0, 0, 1]"));

    ComplexMatrix h(ComplexMatrix_fromString(
            "[0.7071067811865475, 0.7071067811865475]"
            "[0.7071067811865475, -0.7071067811865475]"));

    qDebug() << "";
    qDebug() << m << '\n' << n;
    qDebug() << "+   " << ComplexMatrix_adjoint(h);
    qDebug() << "unit" << ComplexMatrix_mul(h, ComplexMatrix_adjoint(h));

    return 0;
}

