#ifndef COMPLEX_VECTOR_HPP
#define COMPLEX_VECTOR_HPP

#include <QDebug>
#include <QString>

#include "complex.hpp"

class ComplexVector {
public:
    ComplexVector() : _v(nullptr), _length(0) {}
    explicit ComplexVector(int length);
    ComplexVector(const ComplexVector& v_);
    virtual ~ComplexVector();

    ComplexVector& operator=(const ComplexVector& v_) = delete;

    ComplexVector& set(const ComplexVector& v);

    Complex& at(int index) {return _v[index];}
    const Complex& at(int index) const {return _v[index];}

    QString toString(int precision = -1) const;

    static ComplexVector fromString(const QString& s);

    static ComplexVector add(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector sub(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector mul(const ComplexVector& lhs, const Complex& rhs);
    static Complex innerProduct(const ComplexVector& lhs, const ComplexVector& rhs);
    static ComplexVector tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs);

private:
    Complex *_v;
    int _length;
};

QDebug operator<<(QDebug s, const ComplexVector& v);

#endif
