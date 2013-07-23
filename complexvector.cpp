#include "complexvector.hpp"

#include <QStringList>

#include "debug.hpp"

ComplexVector:: ComplexVector(const ComplexVector& v) : _length(v._length) {
    _v = new Complex[_length];
    set(v);
}

ComplexVector::ComplexVector(int length) : _length(length) {
    _v = new Complex[_length];
}

ComplexVector::~ComplexVector() {
    delete[] _v;
}

ComplexVector& ComplexVector::set(const ComplexVector& v) {
    delete[] _v;
    _length = v._length;
    _v = new Complex[_length];
    for (int i = 0; i < v._length; i += 1) {
        at(i).set(v.at(i));
    }
    return *this;
}


QString ComplexVector::toString(int p) const {
    QString ret;
    QTextStream s(&ret);
    s << "[";
    for (int i = 0; i < _length-1; i += 1) {
        s << at(i).toString(p) << ", ";
    }
    if (_length-1 > 0) {
        s << at(_length-1).toString(p);
    }
    s << "]";
    return ret;
}

ComplexVector ComplexVector::fromString(const QString& s_) {
    QString s = s_.trimmed();
    ASSERT(s.contains('[') && s.contains(']'));
    ASSERT(s.indexOf('[') < s.indexOf(']'))

    s.truncate(s.indexOf(']'));
    s.remove(0, s.indexOf('[') + 1);

    QStringList l = s.split(',');

    if (l[0].trimmed().isEmpty() == true) {
        ComplexVector ret(0);
        return ret;
    } else {
        ComplexVector ret(l.size());
        for (int i = 0; i < l.size(); i += 1) {
            ret.at(i).set(Complex::fromString(l[i].trimmed()));
        }
        return ret;
    }
}


ComplexVector ComplexVector::add(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        ret.at(i).set(Complex::add(lhs.at(i), rhs.at(i)));
    }
    return ret;
}

ComplexVector ComplexVector::sub(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        ret.at(i).set(Complex::sub(lhs.at(i), rhs.at(i)));
    }
    return ret;
}

ComplexVector ComplexVector::mul(const ComplexVector& lhs, const Complex& rhs) {
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        ret.at(i).set(Complex::mul(lhs.at(i), rhs));
    }
    return ret;
}

Complex ComplexVector::innerProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    Complex ret(Complex::Zero);
    for (int i = 0; i < lhs._length; i += 1) {
        ret.set(Complex::add(ret, Complex::mul(lhs.at(i), rhs.at(i))));
    }
    return ret;
}

ComplexVector ComplexVector::tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ComplexVector ret(lhs._length * rhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        for (int j = 0; j < rhs._length; j += 1) {
            ret.at(i*rhs._length + j).set(Complex::mul(lhs.at(i), rhs.at(j)));
        }
    }
    return ret;
}

QDebug operator<<(QDebug s, const ComplexVector& v) {
    s << v.toString();
    return s;
}
