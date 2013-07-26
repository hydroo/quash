#ifndef COMPLEX_VECTOR_HPP
#define COMPLEX_VECTOR_HPP

#include <QDebug>
#include <QString>

#include "complex.hpp"

struct ComplexMatrix;

struct ComplexVector {
    ComplexVector(int length = 0);
    ComplexVector(const ComplexVector& v);
    virtual ~ComplexVector();

    Complex* at(int i) {return &_v[i];}
    const Complex& at(int i) const {return _v[i];}

    Complex& operator=(const Complex&) = delete;

    Complex *_v;
    int _length;
};

ComplexVector* ComplexVector_init(int length = 0);

ComplexVector* ComplexVector_set(ComplexVector *v, const ComplexVector& w);

ComplexVector ComplexVector_conjugate(const ComplexVector& v);
bool ComplexVector_isNormalized(const ComplexVector& v);
Real ComplexVector_norm(const ComplexVector& v);
ComplexVector ComplexVector_normalize(const ComplexVector& v);

QString ComplexVector_toString(const ComplexVector& v, int precision = -1);

ComplexVector ComplexVector_fromString(const QString& s);

ComplexVector ComplexVector_add(const ComplexVector& lhs, const ComplexVector& rhs);
ComplexVector ComplexVector_sub(const ComplexVector& lhs, const ComplexVector& rhs);
ComplexVector ComplexVector_mul(const ComplexVector& lhs, const Complex& rhs);
Complex ComplexVector_innerProduct(const ComplexVector& lhs, const ComplexVector& rhs);
ComplexVector ComplexVector_tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs);
Real ComplexVector_distance(const ComplexVector& lhs, const ComplexVector& rhs);

bool ComplexVector_isEqual(const ComplexVector& lhs, const ComplexVector& rhs, double error = 1E-9);

ComplexVector ComplexVector_Zero(int length);
ComplexVector ComplexVector_One(int length);
ComplexVector ComplexVector_Identity(int length, int where); // zero everwhere and one at 'where'

QDebug operator<<(QDebug s, const ComplexVector& v);

#endif
