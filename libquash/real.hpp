#ifndef REAL_HPP
#define REAL_HPP

#include <cmath>

#include <QDebug>
#include <QString>

class Real {
public:

    Real() {}
    Real(const Real& r) : _d(r._d) {}
    virtual ~Real() {}

    Real& operator=(const Real& r) = delete;

    Real& set(Real r) {_d = r._d; return *this;}

    Real arcSine() const {return Real::fromDouble(asin(_d));}
    Real square() const {return Real::fromDouble(_d*_d);}
    Real squareRoot() const {return Real::fromDouble(sqrt(_d));}

    QString toString(int precision = -1, bool removeTrailingZeros = true) const;

    static Real fromDouble(double d) {Real r; r._d = d; return r;}
    static Real fromString(const QString& s);

    static Real add(const Real& lhs, const Real& rhs) {return Real::fromDouble(lhs._d + rhs._d);}
    static Real sub(const Real& lhs, const Real& rhs) {return Real::fromDouble(lhs._d - rhs._d);}
    static Real mul(const Real& lhs, const Real& rhs) {return Real::fromDouble(lhs._d * rhs._d);}
    static Real div(const Real& lhs, const Real& rhs) {return Real::fromDouble(lhs._d / rhs._d);}

    static bool isEqual(const Real& lhs, const Real& rhs, double error = 1E-9) {return (lhs._d - rhs._d) <= error;}
    static bool isSmallerThan(const Real& lhs, const Real& rhs) {return lhs._d < rhs._d;}
    static bool isSmallerEqual(const Real& lhs, const Real& rhs) {return lhs._d <= rhs._d;}
    static bool isGreaterThan(const Real& lhs, const Real& rhs) {return lhs._d > rhs._d;}
    static bool isGreaterEqual(const Real& lhs, const Real& rhs) {return lhs._d >= rhs._d;}

    static const Real Zero;
    static const Real One;
    static const Real MinusOne;

private:
    double _d;
};

QDebug operator<<(QDebug s, const Real& r);

#endif
