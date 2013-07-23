#include "complex.hpp"

#include <QStringList>

#include "debug.hpp"

const Complex Complex::Zero = Complex::fromReal(Real::Zero);
const Complex Complex::One = Complex::fromReal(Real::One);
const Complex Complex::I = Complex::fromReal(Real::Zero, Real::One);

QString Complex::toString(int p) const {
    if (Real::smallerThan(imag(), Real::fromDouble(0))) {
        return QString("%1 - %2i").arg(_r.toString(p)).arg(Real::mul(_i, Real::MinusOne).toString(p));
    } else {
        return QString("%1 + %2i").arg(_r.toString(p)).arg(_i.toString(p));
    }
}

Complex Complex::fromString(const QString& s_) {
    QString s = s_.trimmed();
    Real r, i;

    if (s.contains('i') == false) {
        if (s.startsWith('-') || s.startsWith('+')) {
            ASSERT(s.right(s.size()-1).contains('-') == false && s.right(s.size()-1).contains('+') == false);
        } else {
            ASSERT(s.contains('-') == false && s.contains('+') == false);
        }
        r.set(Real::fromString(s));
        i.set(Real::Zero);
    } else {
        if (s.startsWith('-')) {
            if (s.indexOf('-', 1) == -1 && s.indexOf('+', 1) == -1) { // -#i
                s.prepend("0"); // 0-#i
            }
        }

        if (s.contains('-') == false && s.contains('+') == false) { // #i
            s.prepend("+"); //+#i
        }

        bool rneg = s.startsWith('-');
        if (rneg) {s.remove(0, 1);}

        char sep = s.contains('-') ? '-' : '+';


        QStringList l = s.split(sep);
        ASSERT(l.size() == 2);

        l[0] = l[0].trimmed();
        if (l[0].isEmpty()) {l[0] = "0";}
        l[1] = l[1].remove('i').trimmed();
        if (l[1].isEmpty()) {l[1] = "1";}

        r.set(Real::fromString(rneg ? "-" + l[0] : l[0]));
        i.set(sep == '+' ? Real::fromString(l[1]) : Real::mul(Real::fromString(l[1]), Real::MinusOne));
    }
    return Complex::fromReal(r, i);
}

QDebug operator<<(QDebug s, const Complex& c) {
    s << c.toString();
    return s;
}

