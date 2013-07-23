#ifndef COMPLEX_MATRIX_HPP
#define COMPLEX_MATRIX_HPP

#include <QDebug>
#include <QString>

#include "complex.hpp"
#include "complexvector.hpp"

class ComplexMatrix {
public:
    ComplexMatrix() : _m(nullptr), _height(0), _width(0) {}
    explicit ComplexMatrix(int height, int width);
    ComplexMatrix(const ComplexMatrix& m) {_m = nullptr; set(m);}
    virtual ~ComplexMatrix();

    ComplexMatrix& operator=(const ComplexMatrix& m) = delete;

    ComplexMatrix& set(const ComplexMatrix& m);

    Complex& at(int row_, int col_) {return _m[index(row_, col_)];}
    const Complex& at(int row_, int col_) const {return _m[index(row_, col_)];}
    ComplexVector colAt(int col_) const;
    ComplexVector rowAt(int row_) const;

    ComplexMatrix transpose() const;

    QString toString(int precision = -1) const;

    static ComplexMatrix fromComplexColVector(const ComplexVector& v);
    static ComplexMatrix fromComplexRowVector(const ComplexVector& v);
    static ComplexMatrix fromString(const QString& s);

    static ComplexMatrix add(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
    static ComplexMatrix sub(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
    static ComplexMatrix mul(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
    static ComplexMatrix mul(const ComplexMatrix& lhs, const Complex& rhs);
    static ComplexVector mul(const ComplexMatrix& lhs, const ComplexVector& rhs);
    static ComplexVector mul(const ComplexVector& lhs, const ComplexMatrix& rhs);
    static ComplexMatrix tensorProduct(const ComplexMatrix& lhs, const ComplexMatrix& rhs);

    static ComplexMatrix Zero(int height, int width);
    static ComplexMatrix Identity(int height);

private:

    int index(int row_, int col_) const {return row_*_width + col_;}
    int row(int index) const {return index / _width;}
    int col(int index) const {return index % _width;}

private:
    Complex *_m;
    int _height, _width;
};

QDebug operator<<(QDebug s, const ComplexMatrix& v);

#endif
