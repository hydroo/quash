#include <QDebug>

#include "complex.hpp"
#include "complexvector.hpp"
#include "complexmatrix.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    ComplexVector v(ComplexVector::fromString("[1, i, 1 + i]"));
    ComplexVector w(ComplexVector::fromString("[-1, -i, 1 - i]"));
    Complex c(v.at(0));
    Complex d(v.at(1));



    qDebug() << v;
    qDebug() << w;
    qDebug() << c << ", r " << c.modulus() << ", angle " << c.angle();
    qDebug() << d << ", r " << d.modulus() << ", angle " << d.angle();

    qDebug() << "";
    qDebug() << "+ " << Complex::add(c, d) << ", r " << Complex::add(c, d).modulus() << ", angle " << Complex::add(c, d).angle();
    qDebug() << "- " << Complex::sub(c, d) << ", r " << Complex::sub(c, d).modulus() << ", angle " << Complex::sub(c, d).angle();
    qDebug() << "* " << Complex::mul(c, d) << ", r " << Complex::mul(c, d).modulus() << ", angle " << Complex::mul(c, d).angle();
    qDebug() << "/ " << Complex::div(c, d) << ", r " << Complex::div(c, d).modulus() << ", angle " << Complex::div(c, d).angle();

    qDebug() << "";
    qDebug() << "+ " << ComplexVector::add(v, w);
    qDebug() << "- " << ComplexVector::sub(v, w);
    qDebug() << "* " << ComplexVector::mul(v, Complex::fromString("i"));
    qDebug() << ". " << ComplexVector::innerProduct(v, w);
    qDebug() << "x " << ComplexVector::tensorProduct(v, w);

    ComplexMatrix m(ComplexMatrix::fromString(
            "[1, -i, i]"
            "[0,  1, 0]"
            "[i, -i, 1]"));
    ComplexMatrix n(ComplexMatrix::fromString(
            "[1, 0, 0]"
            "[0, 1, 0]"
            "[0, 0, 1]"));

    qDebug() << "";
    qDebug() << m.toString(0) << '\n' << n.toString(0);
    qDebug() << "+" << ComplexMatrix::add(m,n).toString(0);
    qDebug() << "-" << ComplexMatrix::sub(m,n).toString(0);
    qDebug() << "*" << ComplexMatrix::mul(m,n).toString(0);
    qDebug() << "x" << ComplexMatrix::tensorProduct(m,n).toString(0);
    qDebug() << "*" << ComplexMatrix::mul(n,v).toString(1);
    qDebug() << "*" << ComplexMatrix::mul(v,n).toString(1);

    return 0;
}

