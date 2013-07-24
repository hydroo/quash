#include "complex.hpp"

#include <QStringList>

#include "debug.hpp"

QString Complex_toString(const Complex& c, int p) {
    QString r = Real_toString(Complex_real(c), p);
    QString i = Real_toString(Complex_imag(c), p);

    if (r == "0") {
        if (i == "0") {
            return "0";
        } else if (i == "1") {
            return "i";
        } else if (i == "-1") {
            return "-i";
        } else {
            return i + "i";
        }
    } else {
        if (i == "0") {
            return r;
        } else if (i == "1") {
            return QString("%1 + i").arg(r);
        } else if (i == "-1") {
            return QString("%1 - i").arg(r);
        } else {
            if (Real_isSmallerThan(Complex_imag(c), Real(0))) {
                return QString("%1 - %2i").arg(r).arg(Real_toString(Real_mul(Complex_imag(c), Real_MinusOne), p));
            } else {
                return QString("%1 + %2i").arg(r).arg(Real_toString(Complex_imag(c), p));
            }
        }
    }
}

Complex Complex_fromString(const QString& s_) {
    QString s = s_.trimmed();
    Real r, i;

    if (s.contains('i') == false) {
        if (s.startsWith('-') || s.startsWith('+')) {
            ASSERT(s.right(s.size()-1).contains('-') == false && s.right(s.size()-1).contains('+') == false);
        } else {
            ASSERT(s.contains('-') == false && s.contains('+') == false);
        }
        Real_set(&r, Real_fromString(s));
        Real_set(&i, Real_Zero);
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

        Real_set(&r, Real_fromString(rneg ? "-" + l[0] : l[0]));
        Real_set(&i, sep == '+' ? Real_fromString(l[1]) : Real_mul(Real_fromString(l[1]), Real_MinusOne));
    }
    return Complex(r, i);
}

QDebug operator<<(QDebug s, const Complex& c) {
    s << Complex_toString(c);
    return s;
}

