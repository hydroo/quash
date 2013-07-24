#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <QDebug>
#include <QString>

#include "real.hpp"

struct Complex {
    Complex() {}
    explicit Complex(double r) : _r(Real(r)) {}
    explicit Complex(double r, double i) : _r(Real(r)), _i(Real(i)) {}
    explicit Complex(const Real& r) : _r(r) {}
    explicit Complex(const Real& r, const Real& i) : _r(r), _i(i) {}
    Complex(const Complex& c) : _r(c._r), _i(c._i) {}

    Real _r, _i;
};

inline Complex* Complex_set(Complex *c, const Complex& d) {Real_set(&c->_r, d._r); Real_set(&c->_i, d._i); return c;}

Complex Complex_fromString(const QString& r);

inline const Real& Complex_real(const Complex& c) {return c._r;}
inline const Real& Complex_imag(const Complex& c) {return c._i;}

inline Complex Complex_conjugate(const Complex& c) {return Complex(c._r, Real_mul(Real(-1), c._i));}
inline Real Complex_modulus(const Complex& c) {return Real_squareRoot(Real_add(Real_square(c._r), Real_square(c._i)));}
inline Real Complex_angle(const Complex& c) {Real m = Complex_modulus(c); if (Real_isSmallerEqual(m, Real_Zero)) { return Real_Zero;} else { Real j(c._i); Real_set(&j, Real_div(j, m)); return Real_arcSine(j);}}

QString Complex_toString(const Complex& c, int precision = -1);

inline Complex Complex_add(const Complex& lhs, const Complex& rhs) {return Complex(Real_add(lhs._r, rhs._r), Real_add(lhs._i, rhs._i));}
inline Complex Complex_sub(const Complex& lhs, const Complex& rhs) {return Complex(Real_sub(lhs._r, rhs._r), Real_sub(lhs._i, rhs._i));}
inline Complex Complex_mul(const Complex& lhs, const Complex& rhs) {return Complex(Real_sub(Real_mul(lhs._r, rhs._r), Real_mul(lhs._i, rhs._i)), Real_add(Real_mul(lhs._r, rhs._i), Real_mul(lhs._i, rhs._r)));}
inline Complex Complex_div(const Complex& lhs, const Real& rhs) {return Complex(Real_div(lhs._r, rhs), Real_div(lhs._i, rhs));}
inline Complex Complex_div(const Complex& lhs, const Complex& rhs) {return Complex_div(lhs, Complex_mul(rhs, Complex_conjugate(rhs))._r);}

inline bool Complex_isEqual(const Complex& lhs, const Complex& rhs, double error = 1E-9) {return Real_isEqual(lhs._r, rhs._r, error) && Real_isEqual(lhs._i, rhs._i, error);}

const Complex Complex_Zero = Complex(Real_Zero);
const Complex Complex_One = Complex(Real_One);
const Complex Complex_I = Complex(Real_Zero, Real_One);

QDebug operator<<(QDebug s, const Complex& c);

#endif
