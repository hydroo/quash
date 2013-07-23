#include "complexmatrix.hpp"

#include <QStringList>
#include <QTextStream>

#include "debug.hpp"

ComplexMatrix::ComplexMatrix(int height, int width) : _height(height), _width(width) {
    _m = new Complex[_height*_width];
}

ComplexMatrix::~ComplexMatrix() {
    delete[] _m;
}

ComplexMatrix& ComplexMatrix::set(const ComplexMatrix& m) {
    delete[] _m;
    _height = m._height;
    _width = m._width;
    _m = new Complex[_height*_width];
    for (int i = 0; i < _height; i += 1) {
        for (int j = 0; j < _width; j += 1) {
            at(i, j).set(m.at(i, j));
        }
    }
    return *this;
}

ComplexVector ComplexMatrix::colAt(int col_) const {
    ComplexVector c(_height);
    for (int i = 0; i < _height; i += 1) {
        c.at(i).set(at(i, col_));
    }
    return c;
}

ComplexVector ComplexMatrix::rowAt(int row_) const {
    ComplexVector c(_width);
    for (int i = 0; i < _width; i += 1) {
        c.at(i).set(at(row_, i));
    }
    return c;
}

ComplexMatrix ComplexMatrix::transpose() const {
    ComplexMatrix m(_width, _height);
    for (int i = 0; i < _width; i += 1) {
        for (int j = 0; j < _height; j += 1) {
            m.at(i, j).set(at(j, i));
        }
    }
    return m; 
}

QString ComplexMatrix::toString(int precision) const {

    QString s[_height][_width];
    int maxLen[_width];
    for (int i = 0; i < _width; i += 1) {maxLen[i] = 0;}

    for (int i = 0; i < _height; i += 1) {
        for (int j = 0; j < _width; j += 1) {
            s[i][j] = at(i, j).toString(precision);
            maxLen[j] = qMax(maxLen[j], s[i][j].size());
        }
    }

    QString ret;
    QTextStream ss(&ret);

    for (int i = 0; i < _height; i += 1) {
        ss << "[";
        for (int j = 0; j < _width; j += 1) {
            int pad = maxLen[j] - s[i][j].size();
            for (int k = 0; k < pad; k += 1) {ss << " ";}
            ss << s[i][j];
            if (j < _width - 1) { ss << ", "; }
        }
        ss << "]";
        if (i < _height-1) {ss << "\n";}
    }
    return ret;
}

ComplexMatrix ComplexMatrix::fromComplexColVector(const ComplexVector& v) {
    ComplexMatrix m(v._length, 1);
    for (int i = 0; i < m._height; i += 1) {
        m.at(i, 0).set(v.at(i));
    }
    return m;
}

ComplexMatrix ComplexMatrix::fromComplexRowVector(const ComplexVector& v) {
    ComplexMatrix m(1, v._length);
    for (int i = 0; i < m._width; i += 1) {
        m.at(0, i).set(v.at(i));
    }
    return m;
}

ComplexMatrix ComplexMatrix::fromString(const QString& s_) {
    QString s = s_.trimmed();
    int width, height = s.count('[');

    QStringList rows = s.split('[', QString::SkipEmptyParts);
    height = rows.size();

    if (height == 0) {
        return ComplexMatrix(0, 0);
    }

    width = rows[0].count(',') + 1;

    ComplexMatrix m(height, width);

    for (int i = 0; i < height; i += 1) {
        rows[i] = rows[i].remove(']').remove('\n').trimmed();
        QStringList cells = rows[i].split(',', QString::SkipEmptyParts);
        ASSERT(width == cells.size());

        for (int j = 0; j < width; j += 1) {
            m.at(i, j).set(Complex::fromString(cells[j].trimmed()));
        }
    }

    return m;
}

ComplexMatrix ComplexMatrix::add(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._height == rhs._height && lhs._width == rhs._width);
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            m.at(i, j).set(Complex::add(lhs.at(i, j), rhs.at(i, j)));
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix::sub(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._height == rhs._height && lhs._width == rhs._width);
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            m.at(i, j).set(Complex::sub(lhs.at(i, j), rhs.at(i, j)));
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix::mul(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._width == rhs._height);
    ComplexMatrix m(lhs._height, rhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < rhs._width; j += 1) {
            m.at(i, j).set(ComplexVector::innerProduct(lhs.rowAt(i), rhs.colAt(j)));
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix::mul(const ComplexMatrix& lhs, const Complex& rhs) {
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            m.at(i, j).set(Complex::mul(lhs.at(i, j), rhs));
        }
    }
    return m;
}

ComplexVector ComplexMatrix::mul(const ComplexMatrix& lhs, const ComplexVector& rhs) {
    return ComplexMatrix::mul(lhs, ComplexMatrix::fromComplexColVector(rhs)).colAt(0);
}

ComplexVector ComplexMatrix::mul(const ComplexVector& lhs, const ComplexMatrix& rhs) {
    return ComplexMatrix::mul(ComplexMatrix::fromComplexRowVector(lhs), rhs).rowAt(0);
}

ComplexMatrix ComplexMatrix::tensorProduct(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ComplexMatrix m(lhs._height*rhs._height, lhs._width*rhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            for (int k = 0; k < rhs._height; k += 1) {
                for (int l = 0; l < rhs._width; l += 1) {
                    m.at(i*lhs._height + k, j*lhs._width + l).set(Complex::mul(lhs.at(i, j), rhs.at(k, l)));
                }
            }
        }
    }
    return m;
}

//ComplexMatrix ComplexMatrix::Zero(int height, int width) {
//}
//
//ComplexMatrix ComplexMatrix::Identity(int height) {
//}
//
QDebug operator<<(QDebug s, const ComplexMatrix& v) {
    s << v.toString();
    return s;
}
