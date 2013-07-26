#ifndef REAL_HPP
#define REAL_HPP

#include <cmath>

#include <QDebug>
#include <QString>

struct Real {
    Real() {}
    explicit Real(double d) : _d(d) {}
    Real(const Real& r) : _d(r._d) {}

    double _d;
};

inline Real* Real_set(Real *r, const Real& s) {r->_d = s._d; return r;}

Real Real_fromString(const QString& s);

inline Real Real_arcSine(const Real &r) {return Real(asin(r._d));}
inline Real Real_square(const Real &r) {return Real(r._d*r._d);}
inline Real Real_squareRoot(const Real &r) {return Real(sqrt(r._d));}

QString Real_toString(const Real& r, int precision = -1, bool removeTrailingZeros = true);

inline Real Real_add(const Real& lhs, const Real& rhs) {return Real(lhs._d + rhs._d);}
inline Real Real_sub(const Real& lhs, const Real& rhs) {return Real(lhs._d - rhs._d);}
inline Real Real_mul(const Real& lhs, const Real& rhs) {return Real(lhs._d * rhs._d);}
inline Real Real_div(const Real& lhs, const Real& rhs) {return Real(lhs._d / rhs._d);}

inline bool Real_isEqual(const Real& lhs, const Real& rhs, double error = 1E-9) {return (lhs._d - rhs._d) <= error;}
inline bool Real_isSmallerThan(const Real& lhs, const Real& rhs) {return lhs._d < rhs._d;}
inline bool Real_isSmallerEqual(const Real& lhs, const Real& rhs) {return lhs._d <= rhs._d;}
inline bool Real_isGreaterThan(const Real& lhs, const Real& rhs) {return lhs._d > rhs._d;}
inline bool Real_isGreaterEqual(const Real& lhs, const Real& rhs) {return lhs._d >= rhs._d;}

const Real Real_One = Real(1);
const Real Real_MinusOne = Real(-1);
const Real Real_Zero = Real(0);

QDebug operator<<(QDebug s, const Real& r);


#endif
