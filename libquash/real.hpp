#ifndef REAL_HPP
#define REAL_HPP

#include <cmath>

#include <QDebug>
#include <QString>

struct Real {
    double _d;
};

inline Real* Real_set(Real *r, const Real& s) {r->_d = s._d; return r;}

inline Real Real_fromDouble(double d) {Real r; r._d = d; return r;}
Real Real_fromString(const QString& s);

inline Real Real_arcSine(const Real &r) {return Real_fromDouble(asin(r._d));}
inline Real Real_square(const Real &r) {return Real_fromDouble(r._d*r._d);}
inline Real Real_squareRoot(const Real &r) {return Real_fromDouble(sqrt(r._d));}

QString Real_toString(const Real& r, int precision = -1, bool removeTrailingZeros = true);

inline Real Real_add(const Real& lhs, const Real& rhs) {return Real_fromDouble(lhs._d + rhs._d);}
inline Real Real_sub(const Real& lhs, const Real& rhs) {return Real_fromDouble(lhs._d - rhs._d);}
inline Real Real_mul(const Real& lhs, const Real& rhs) {return Real_fromDouble(lhs._d * rhs._d);}
inline Real Real_div(const Real& lhs, const Real& rhs) {return Real_fromDouble(lhs._d / rhs._d);}

inline bool Real_isEqual(const Real& lhs, const Real& rhs, double error = 1E-9) {return (lhs._d - rhs._d) <= error;}
inline bool Real_isSmallerThan(const Real& lhs, const Real& rhs) {return lhs._d < rhs._d;}
inline bool Real_isSmallerEqual(const Real& lhs, const Real& rhs) {return lhs._d <= rhs._d;}
inline bool Real_isGreaterThan(const Real& lhs, const Real& rhs) {return lhs._d > rhs._d;}
inline bool Real_isGreaterEqual(const Real& lhs, const Real& rhs) {return lhs._d >= rhs._d;}

const Real Real_Zero = Real_fromDouble(0);
const Real Real_One = Real_fromDouble(1);
const Real Real_MinusOne = Real_fromDouble(-1);

QDebug operator<<(QDebug s, const Real& r);


#endif
