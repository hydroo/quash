#include "complexvector.hpp"

#include <QStringList>

#include "debug.hpp"

ComplexVector::ComplexVector(int length) : _length(length) {
    if (length == 0) {
        _v = nullptr;
    } else {
        _v = (Complex*) malloc(sizeof(Complex) * length);
    }
}

ComplexVector::ComplexVector(const ComplexVector& v) {
    _v = nullptr;
    ComplexVector_set(this, v);
}

ComplexVector::~ComplexVector() {
    delete[] _v;
}

ComplexVector* ComplexVector_set(ComplexVector* v, const ComplexVector& w) {
    delete[] v->_v;
    v->_length = w._length;
    v->_v = new Complex[v->_length];
    for (int i = 0; i < v->_length; i += 1) {
        Complex_set(ComplexVector_at(v, i), w[i]);
    }
    return v;
}

ComplexVector ComplexVector_conjugate(const ComplexVector& v) {
    ComplexVector w(v._length);
    for (int i = 0; i < v._length; i += 1) {
        Complex_set(ComplexVector_at(&w, i), Complex_conjugate(v[i]));
    }
    return w;
}

bool ComplexVector_isNormalized(const ComplexVector& v) {
    return ComplexVector_isEqual(v, ComplexVector_normalize(v));
}

Real ComplexVector_norm(const ComplexVector& v) {
    return Real_squareRoot(Complex_real(ComplexVector_innerProduct(v, v)));
}

ComplexVector ComplexVector_normalize(const ComplexVector& v) {
    Real n = ComplexVector_norm(v);
    ComplexVector w(v._length);
    for (int i = 0; i < v._length; i += 1) {
        Complex_set(ComplexVector_at(&w, i), Complex_div(v[i], n));
    }
    return w;
}

QString ComplexVector_toString(const ComplexVector& v, int p) {
    QString ret;
    QTextStream s(&ret);
    s << "[";
    for (int i = 0; i < v._length-1; i += 1) {
        s << Complex_toString(v[i], p) << ", ";
    }
    if (v._length-1 > 0) {
        s << Complex_toString(v[v._length-1], p);
    }
    s << "]";
    return ret;
}

ComplexVector ComplexVector_fromString(const QString& s_) {
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
            Complex_set(ComplexVector_at(&ret, i), Complex_fromString(l[i].trimmed()));
        }
        return ret;
    }
}


ComplexVector ComplexVector_add(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(ComplexVector_at(&ret, i), Complex_add(lhs[i], rhs[i]));
    }
    return ret;
}

ComplexVector ComplexVector_sub(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(ComplexVector_at(&ret, i), Complex_sub(lhs[i], rhs[i]));
    }
    return ret;
}

ComplexVector ComplexVector_mul(const ComplexVector& lhs, const Complex& rhs) {
    ComplexVector ret(lhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(ComplexVector_at(&ret, i), Complex_mul(lhs[i], rhs));
    }
    return ret;
}

Complex ComplexVector_innerProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ASSERT(lhs._length == rhs._length);
    Complex ret(Complex_Zero);
    for (int i = 0; i < lhs._length; i += 1) {
        Complex_set(&ret, Complex_add(ret, Complex_mul(Complex_conjugate(lhs[i]), rhs[i])));
    }
    return ret;
}

ComplexVector ComplexVector_tensorProduct(const ComplexVector& lhs, const ComplexVector& rhs) {
    ComplexVector ret(lhs._length * rhs._length);
    for (int i = 0; i < lhs._length; i += 1) {
        for (int j = 0; j < rhs._length; j += 1) {
            Complex_set(ComplexVector_at(&ret, i*rhs._length + j), Complex_mul(lhs[i], rhs[j]));
        }
    }
    return ret;
}

Real ComplexVector_distance(const ComplexVector& lhs, const ComplexVector& rhs) {
    return ComplexVector_norm(ComplexVector_sub(lhs, rhs));
}

bool ComplexVector_isEqual(const ComplexVector& lhs, const ComplexVector& rhs, double error) {
    ASSERT(lhs._length == rhs._length);
    bool equal = true;
    for (int i = 0; i < lhs._length; i += 1) {
        equal &= Complex_isEqual(lhs[i], rhs[i], error);
    }
    return equal;
}

ComplexVector ComplexVector_Zero(int length) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(ComplexVector_at(&v, i), Complex_Zero);}
    return v;
}

ComplexVector ComplexVector_One(int length) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(ComplexVector_at(&v, i), Complex_One);}
    return v;
}

ComplexVector ComplexVector_Identity(int length, int where) {
    ComplexVector v(length);
    for (int i = 0; i < length; i += 1) {Complex_set(ComplexVector_at(&v, i), Complex_Zero);}
    Complex_set(ComplexVector_at(&v, where), Complex_One);
    return v;
}

QDebug operator<<(QDebug s, const ComplexVector& v) {
    s << ComplexVector_toString(v);
    return s;
}
