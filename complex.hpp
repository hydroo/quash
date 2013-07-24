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

    Complex& set(const Complex& c) {_r.set(c._r); _i.set(c._i); return *this;}

    const Real& real() const {return _r;}
    const Real& imag() const {return _i;}

    Complex conjugate() const {return Complex::fromReal(_r, Real::mul(Real::fromDouble(-1), _i));}
    Real modulus() const {return Real::add(_r.square(), _i.square()).squareRoot();}
    Real angle() const {Real m = this->modulus(); if (Real::isSmallerEqual(m, Real::Zero)) { return Real::Zero;} else { Real j(_i); j.set(Real::div(j, m)); return j.arcSine();}}

    QString toString(int precision = -1) const;

    static Complex fromDouble(double r) {return Complex::fromDouble (r, 0);}
    static Complex fromDouble(double r, double i) {return Complex::fromReal(Real::fromDouble(r), Real::fromDouble(i));}
    static Complex fromReal(const Real& r) {Complex c; c._r.set(r); c._i.set(Real::fromDouble(0)); return c;}
    static Complex fromReal(const Real& r, const Real& i) {Complex c; c._r.set(r); c._i.set(i); return c;}
    static Complex fromString(const QString& r);

    static Complex add(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real::add(lhs._r, rhs._r), Real::add(lhs._i, rhs._i));}
    static Complex sub(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real::sub(lhs._r, rhs._r), Real::sub(lhs._i, rhs._i));}
    static Complex mul(const Complex& lhs, const Complex& rhs) {return Complex::fromReal(Real::sub(Real::mul(lhs._r, rhs._r), Real::mul(lhs._i, rhs._i)), Real::add(Real::mul(lhs._r, rhs._i), Real::mul(lhs._i, rhs._r)));}
    static Complex  div(const Complex& lhs, const Complex& rhs) {return Complex::div(lhs, Complex::mul(rhs, rhs.conjugate())._r);}
    static Complex  div(const Complex& lhs, const Real& rhs) {return Complex::fromReal(Real::div(lhs._r, rhs), Real::div(lhs._i, rhs));}

    static bool isEqual(const Complex& lhs, const Complex& rhs, double error = 1E-9) {return Real::isEqual(lhs._r, rhs._r, error) && Real::isEqual(lhs._i, rhs._i, error);}

    static const Complex Zero;
    static const Complex One;
    static const Complex I;

private:
    Real _r, _i;
};

QDebug operator<<(QDebug s, const Complex& c);

#endif
