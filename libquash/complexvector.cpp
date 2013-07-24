#include "complexvector.hpp"

#include <QStringList>

#include "debug.hpp"

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
    for (int i = 0; i < _length; i += 1) {
        Complex_set(&at(i), v.at(i));
    }
    return *this;
}

ComplexVector ComplexVector::conjugate() const {
    ComplexVector v(_length);
    for (int i = 0; i < _length; i += 1) {
        Complex_set(&v.at(i), Complex_conjugate(at(i)));
    }
    return v;
}

bool ComplexVector::isNormalized() const {
    return ComplexVector::isEqual(*this, this->normalize());
}

Real ComplexVector::norm() const {
    return Real_squareRoot(Complex_real(ComplexVector::innerProduct(*this, *this)));
}

ComplexVector ComplexVector::normalize() const {
    Real n = norm();
    ComplexVector v(_length);
    for (int i = 0; i < _length; i += 1) {
        Complex_set(&v.at(i), Complex_div(at(i), n));
    }
    return v;
}

QString ComplexVector::toString(int p) const {
    QString ret;
    QTextStream s(&ret);
    s << "[";
    for (int i = 0; i < _length-1; i += 1) {
        s << Complex_toString(at(i), p) << ", ";
    }
    if (_length-1 > 0) {
        s << Complex_toString(at(_length-1), p);
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
            Complex_set(&ret.at(i), Complex_fromString(l[i].trimmed()));
        }
        return ret;
    }
}


ComplexVector ComplexVector::add(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(&ret.at(i), Complex_add(lhs.at(i), rhs.at(i)));
    }
    return ret;
}

ComplexVector ComplexVector::sub(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(&ret.at(i), Complex_sub(lhs.at(i), rhs.at(i)));
    }
    return ret;
}

ComplexVector ComplexVector::mul(const ComplexVector& lhs, const Complex& rhs) {
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(&ret.at(i), Complex_mul(lhs.at(i), rhs));
    }
    return ret;
}

Complex ComplexVector::innerProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    Complex ret(Complex_Zero);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(&ret, Complex_add(ret, Complex_mul(Complex_conjugate(lhs.at(i)), rhs.at(i))));
    }
    return ret;
}

ComplexVector ComplexVector::tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ComplexVector ret(lhs._length * rhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        for (int j = 0; j < rhs._length; j += 1) {
            Complex_set(&ret.at(i*rhs._length + j), Complex_mul(lhs.at(i), rhs.at(j)));
        }
    }
    return ret;
}

Real ComplexVector::distance(const ComplexVector& lhs, const ComplexVector& rhs) {
    return ComplexVector::sub(lhs, rhs).norm();
}

bool ComplexVector::isEqual(const ComplexVector& lhs, const ComplexVector& rhs, double error) {
    ASSERT(lhs._length == rhs._length);
    bool equal = true;
    for (int i = 0; i < lhs._length; i += 1) {
        equal &= Complex_isEqual(lhs.at(i), rhs.at(i), error);
    }
    return equal;
}

ComplexVector ComplexVector::Zero(int length) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(&v.at(i), Complex_Zero);}
    return v;
}

ComplexVector ComplexVector::One(int length) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(&v.at(i), Complex_One);}
    return v;
}

ComplexVector ComplexVector::Identity(int length, int where) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(&v.at(i), Complex_Zero);}
    Complex_set(&v.at(where), Complex_One);
    return v;
}

QDebug operator<<(QDebug s, const ComplexVector& v) {
    s << v.toString();
    return s;
}
