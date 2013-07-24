#ifndef COMPLEX_VECTOR_HPP
#define COMPLEX_VECTOR_HPP

#include <QDebug>
#include <QString>

#include "complex.hpp"

struct ComplexMatrix;

class ComplexVector {
public:
    ComplexVector() : _v(nullptr), _length(0) {}
    explicit ComplexVector(int length);
    ComplexVector(const ComplexVector& v) {_v = nullptr; set(v);}
    virtual ~ComplexVector();

    ComplexVector& operator=(const ComplexVector& v) = delete;

    ComplexVector& set(const ComplexVector& v);

    Complex& at(int index) {return _v[index];}
    const Complex& at(int index) const {return _v[index];}

    ComplexVector conjugate() const;
    Real norm() const;

    QString toString(int precision = -1) const;

    static ComplexVector fromString(const QString& s);

    static ComplexVector add(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector sub(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector mul(const ComplexVector& lhs, const Complex& rhs);
    static Complex innerProduct(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs);
    static Real distance(const ComplexVector& lhs, const ComplexVector& rhs);

    static bool isEqual(const ComplexVector& lhs, const ComplexVector& rhs, double error = 1E-9);

    static ComplexVector Zero(int length);
    static ComplexVector One(int length);
    static ComplexVector Identity(int length, int where); // zero everwhere and one at 'where'

    friend ComplexMatrix;

private:
    Complex *_v;
    int _length;
};

QDebug operator<<(QDebug s, const ComplexVector& v);

#endif
