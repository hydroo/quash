#ifndef COMPLEX_MATRIX_HPP
#define COMPLEX_MATRIX_HPP

#include <QDebug>
#include <QString>

#include "complex.hpp"
#include "complexvector.hpp"

struct ComplexMatrix {
    ComplexMatrix(int height = 0, int width = 0);
    ComplexMatrix(const ComplexMatrix& m);
    virtual ~ComplexMatrix();

    Complex* at(int row, int col) {return &(_m[row*_width + col]);}
    const Complex& at(int row, int col) const {return _m[row*_width + col];}

    Complex& operator=(const Complex&) = delete;

    Complex *_m;
    int _height, _width;
};

ComplexMatrix* ComplexMatrix_set(ComplexMatrix* m, const ComplexMatrix& n);

ComplexVector ComplexMatrix_colAt(const ComplexMatrix& m, int col_);
ComplexVector ComplexMatrix_rowAt(const ComplexMatrix& m, int row_);

ComplexMatrix ComplexMatrix_adjoint(const ComplexMatrix& m);
ComplexMatrix ComplexMatrix_conjugate(const ComplexMatrix& m);
bool ComplexMatrix_isHermitian(const ComplexMatrix& m);
bool ComplexMatrix_isUnitary(const ComplexMatrix& m);
ComplexMatrix ComplexMatrix_transpose(const ComplexMatrix& m);

QString ComplexMatrix_toString(const ComplexMatrix& m, int precision = -1);

ComplexMatrix ComplexMatrix_fromComplexColVector(const ComplexVector& v);
ComplexMatrix ComplexMatrix_fromComplexRowVector(const ComplexVector& v);
ComplexMatrix ComplexMatrix_fromString(const QString& s);

ComplexMatrix ComplexMatrix_add(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
ComplexMatrix ComplexMatrix_sub(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
ComplexMatrix ComplexMatrix_mul(const ComplexMatrix& lhs, const ComplexMatrix& rhs);
ComplexMatrix ComplexMatrix_mul(const ComplexMatrix& lhs, const Complex& rhs);
ComplexVector ComplexMatrix_mul(const ComplexMatrix& lhs, const ComplexVector& rhs);
ComplexVector ComplexMatrix_mul(const ComplexVector& lhs, const ComplexMatrix& rhs);
ComplexMatrix ComplexMatrix_tensorProduct(const ComplexMatrix& lhs, const ComplexMatrix& rhs);

bool ComplexMatrix_isEqual(const ComplexMatrix& lhs, const ComplexMatrix& rhs, double error = 1E-9);

ComplexMatrix ComplexMatrix_Identity(int height);
ComplexMatrix ComplexMatrix_Zero(int height);

const ComplexMatrix ComplexMatrix_Hadamard = ComplexMatrix_fromString(
        "[0.7071067811865475,  0.7071067811865475]"
        "[0.7071067811865475, -0.7071067811865475]");

QDebug operator<<(QDebug s, const ComplexMatrix& v);

#endif
