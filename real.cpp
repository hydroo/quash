#include "real.hpp"

#include "debug.hpp"
#include "misc.hpp"

const Real Real::Zero = Real::fromDouble(0);
const Real Real::One = Real::fromDouble(1);
const Real Real::MinusOne = Real::fromDouble(-1);

QString Real::toString(int p) const {
    if (p == -1) {
        return removeTrailingZeros(QString("%1").arg(_d, 0, 'f', p));
    } else {
        return QString("%1").arg(_d, 0, 'f', p);
    }
}

Real Real::fromString(const QString& s) {
    bool ok;
    double d = s.trimmed().toDouble(&ok);
    ASSERT(ok);
    return Real::fromDouble(d);
}

QDebug operator<<(QDebug s, const Real& r) {
    s << r.toString();
    return s;
}

