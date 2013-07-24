#include "real.hpp"

#include "debug.hpp"
#include "misc.hpp"

QString Real_toString(const Real& r, int p, bool rem) {
    if (rem) {
        return removeTrailingZeros(QString("%1").arg(r._d, 0, 'f', p));
    } else {
        return QString("%1").arg(r._d, 0, 'f', p);
    }
}

Real Real_fromString(const QString& s) {
    bool ok;
    double d = s.trimmed().toDouble(&ok);
    ASSERT(ok);
    return Real(d);
}

QDebug operator<<(QDebug s, const Real& r) {
    s << Real_toString(r);
    return s;
}

