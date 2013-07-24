#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <QDebug>
#include <QString>

#include "real.hpp"

class Complex {
public:
    Complex() {}
    Complex(const Complex& c) : _r(c._r), _i(c._i) {}
    virtual ~Complex() {}

    Complex& operator=(const Complex& a) = delete;

    Complex& set(const Complex& c) {Real_set(&_r, c._r); Real_set(&_i, c._i); return *this;}

    const Real& real() const {return _r;}
    const Real& imag() const {return _i;}

    Complex conjugate() const {return Complex::fromReal(_r, Real_mul(Real_fromDouble(-1), _i));}
    Real modulus() const {return Real_squareRoot(Real_add(Real_square(_r), Real_square(_i)));}
    Real angle() const {Real m = this->modulus(); if (Real_isSmallerEqual(m, Real_Zero)) { return Real_Zero;} else { Real j(_i); Real_set(&j, Real_div(j, m)); return Real_arcSine(j);}}

    QString toString(int precision = -1) const;

    static Complex fromDouble(double r) {return Complex::fromDouble (r, 0);}
    static Complex fromDouble(double r, double i) {return Complex::fromReal(Real_fromDouble(r), Real_fromDouble(i));}
    static Complex fromReal(const Real& r) {Complex c; Real_set(&c._r, r); Real_set(&c._i, Real_fromDouble(0)); return c;}
    static Complex fromReal(const Real& r, const Real& i) {Complex c; Real_set(&c._r, r); Real_set(&c._i, i); return c;}
    static Complex fromString(const QString& r);

    static Complex add(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real_add(lhs._r, rhs._r), Real_add(lhs._i, rhs._i));}
    static Complex sub(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real_sub(lhs._r, rhs._r), Real_sub(lhs._i, rhs._i));}
    static Complex mul(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real_sub(Real_mul(lhs._r, rhs._r), Real_mul(lhs._i, rhs._i)), Real_add(Real_mul(lhs._r, rhs._i), Real_mul(lhs._i, rhs._r)));}
    static Complex  div(const Complex& lhs, const Complex& rhs) {return Complex::div(lhs, Complex::mul(rhs, rhs.conjugate())._r);}
    static Complex  div(const Complex& lhs, const Real& rhs) {return Complex::fromReal(Real_div(lhs._r, rhs), Real_div(lhs._i, rhs));}

    static bool isEqual(const Complex& lhs, const Complex& rhs, double error = 1E-9) {return Real_isEqual(lhs._r, rhs._r, error) && Real_isEqual(lhs._i, rhs._i, error);}

    static const Complex Zero;
    static const Complex One;
    static const Complex I;

private:
    Real _r, _i;
};

QDebug operator<<(QDebug s, const Complex& c);

#endif
