#include "complexmatrix.hpp"

#include <QStringList>
#include <QTextStream>

#include "debug.hpp"

/* *** helper { ************************************************************ */

static inline int indexFromRowCol(const ComplexMatrix& m, int row_, int col_) {return row_*m._width + col_;}
static inline int rowFromIndex(const ComplexMatrix& m, int index) {return index / m._width;}
static inline int colFromIndex(const ComplexMatrix& m, int index) {return index % m._width;}

/* *** } helper ************************************************************ */

ComplexMatrix::ComplexMatrix(int height, int width) : _height(height), _width(width) {
    if (_height == 0 || _width == 0) {
        _m = nullptr;
    } else {
        _m = new Complex[_height*_width];
    }
}

ComplexMatrix::ComplexMatrix(const ComplexMatrix& m) {
    _m = nullptr;
    ComplexMatrix_set(this, m);
}

ComplexMatrix::~ComplexMatrix() {
    delete[] _m;
}

ComplexMatrix* ComplexMatrix_set(ComplexMatrix* m, const ComplexMatrix& n) {
    delete[] m->_m;
    m->_height = n._height;
    m->_width = n._width;
    m->_m = new Complex[m->_height*m->_width];
    for (int i = 0; i < m->_height; i += 1) {
        for (int j = 0; j < m->_width; j += 1) {
            Complex_set(ComplexMatrix_at(m, i, j), ComplexMatrix_at(n, i,j));
        }
    }
    return m;
}

ComplexVector ComplexMatrix_colAt(const ComplexMatrix& m, int col_) {
    ComplexVector c(m._height);
    for (int i = 0; i < m._height; i += 1) {
        Complex_set(ComplexVector_at(&c, i), ComplexMatrix_at(m, i, col_));
    }
    return c;
}

ComplexVector ComplexMatrix_rowAt(const ComplexMatrix& m, int row_) {
    ComplexVector c(m._width);
    for (int i = 0; i < m._width; i += 1) {
        Complex_set(ComplexVector_at(&c, i), ComplexMatrix_at(m, row_, i));
    }
    return c;
}

ComplexMatrix ComplexMatrix_adjoint(const ComplexMatrix& m) {
    return ComplexMatrix_transpose(ComplexMatrix_conjugate(m));
}

ComplexMatrix ComplexMatrix_conjugate(const ComplexMatrix& m) {
    ComplexMatrix n(m._height, m._width);
    for (int i = 0; i < n._height; i += 1) {
        for (int j = 0; j < n._width; j += 1) {
            Complex_set(ComplexMatrix_at(&n, i, j), Complex_conjugate(ComplexMatrix_at(m, i, j)));
        }
    }
    return n;
}

bool ComplexMatrix_isHermitian(const ComplexMatrix& m) {
    return ComplexMatrix_isEqual(m, ComplexMatrix_adjoint(m));
}

bool ComplexMatrix_isUnitary(const ComplexMatrix& m) {
    return ComplexMatrix_isEqual(ComplexMatrix_Identity(m._height), ComplexMatrix_mul(m, ComplexMatrix_adjoint(m)));
}

ComplexMatrix ComplexMatrix_transpose(const ComplexMatrix& m) {
    ComplexMatrix n(m._width, m._height);
    for (int i = 0; i < n._width; i += 1) {
        for (int j = 0; j < n._height; j += 1) {
            Complex_set(ComplexMatrix_at(&n, i, j), ComplexMatrix_at(m, j, i));
        }
    }
    return n; 
}

QString ComplexMatrix_toString(const ComplexMatrix& m, int precision) {

    QString s[m._height][m._width];
    int maxLen[m._width];
    for (int i = 0; i < m._width; i += 1) {maxLen[i] = 0;}

    for (int i = 0; i < m._height; i += 1) {
        for (int j = 0; j < m._width; j += 1) {
            s[i][j] = Complex_toString(ComplexMatrix_at(m, i, j), precision);
            maxLen[j] = qMax(maxLen[j], s[i][j].size());
        }
    }

    QString ret;
    QTextStream ss(&ret);

    for (int i = 0; i < m._height; i += 1) {
        ss << "[";
        for (int j = 0; j < m._width; j += 1) {
            int pad = maxLen[j] - s[i][j].size();
            for (int k = 0; k < pad; k += 1) {ss << " ";}
            ss << s[i][j];
            if (j < m._width - 1) { ss << ", "; }
        }
        ss << "]";
        if (i < m._height-1) {ss << "\n";}
    }
    return ret;
}

ComplexMatrix ComplexMatrix_fromComplexColVector(const ComplexVector& v) {
    ComplexMatrix m(v._length, 1);
    for (int i = 0; i < m._height; i += 1) {
        Complex_set(ComplexMatrix_at(&m, i, 0), v[i]);
    }
    return m;
}

ComplexMatrix ComplexMatrix_fromComplexRowVector(const ComplexVector& v) {
    ComplexMatrix m(1, v._length);
    for (int i = 0; i < m._width; i += 1) {
        Complex_set(ComplexMatrix_at(&m, 0, i), v[i]);
    }
    return m;
}

ComplexMatrix ComplexMatrix_fromString(const QString& s_) {
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
            Complex_set(ComplexMatrix_at(&m, i, j), Complex_fromString(cells[j].trimmed()));
        }
    }

    return m;
}

ComplexMatrix ComplexMatrix_add(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._height == rhs._height && lhs._width == rhs._width);
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            Complex_set(ComplexMatrix_at(&m, i, j), Complex_add(ComplexMatrix_at(lhs, i, j), ComplexMatrix_at(rhs, i, j)));
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix_sub(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._height == rhs._height && lhs._width == rhs._width);
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            Complex_set(ComplexMatrix_at(&m, i, j), Complex_sub(ComplexMatrix_at(lhs, i, j), ComplexMatrix_at(rhs, i, j)));
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix_mul(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ASSERT(lhs._width == rhs._height);
    ComplexMatrix m(lhs._height, rhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < rhs._width; j += 1) {
            Complex_set(ComplexMatrix_at(&m, i, j), Complex_Zero);
            for (int k = 0; k < lhs._width; k += 1) {
                Complex_set(ComplexMatrix_at(&m, i, j), Complex_add(ComplexMatrix_at(m, i, j), Complex_mul(ComplexMatrix_at(lhs, i, k), ComplexMatrix_at(rhs, k, j))));
            }
        }
    }
    return m;
}

ComplexMatrix ComplexMatrix_mul(const ComplexMatrix& lhs, const Complex& rhs) {
    ComplexMatrix m(lhs._height, lhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            Complex_set(ComplexMatrix_at(&m, i, j), Complex_mul(ComplexMatrix_at(lhs, i, j), rhs));
        }
    }
    return m;
}

ComplexVector ComplexMatrix_mul(const ComplexMatrix& lhs, const ComplexVector& rhs) {
    return ComplexMatrix_colAt(ComplexMatrix_mul(lhs, ComplexMatrix_fromComplexColVector(rhs)), 0);
}

ComplexVector ComplexMatrix_mul(const ComplexVector& lhs, const ComplexMatrix& rhs) {
    return ComplexMatrix_rowAt(ComplexMatrix_mul(ComplexMatrix_fromComplexRowVector(lhs), rhs), 0);
}

ComplexMatrix ComplexMatrix_tensorProduct(const ComplexMatrix& lhs, const ComplexMatrix& rhs) {
    ComplexMatrix m(lhs._height*rhs._height, lhs._width*rhs._width);
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            for (int k = 0; k < rhs._height; k += 1) {
                for (int l = 0; l < rhs._width; l += 1) {
                    Complex_set(ComplexMatrix_at(&m, i*lhs._height + k, j*lhs._width + l), Complex_mul(ComplexMatrix_at(lhs, i, j), ComplexMatrix_at(rhs, k, l)));
                }
            }
        }
    }
    return m;
}

bool ComplexMatrix_isEqual(const ComplexMatrix& lhs, const ComplexMatrix& rhs, double error) {
    ASSERT(lhs._height == rhs._height && lhs._width == rhs._width);
    bool equal = true;
    for (int i = 0; i < lhs._height; i += 1) {
        for (int j = 0; j < lhs._width; j += 1) {
            equal &= Complex_isEqual(ComplexMatrix_at(lhs, i, j), ComplexMatrix_at(rhs, i, j), error);
        }
    }
    return equal;
}

ComplexMatrix ComplexMatrix_Identity(int height) {
    ComplexMatrix m(height, height);
    for (int i = 0; i < height; i += 1) {
        for (int j = 0; j < height; j += 1) {
            if (i == j) {
                Complex_set(ComplexMatrix_at(&m, i, j), Complex_One);
            } else {
                Complex_set(ComplexMatrix_at(&m, i, j), Complex_Zero);
            }
        }
    }
    return m;
}

QDebug operator<<(QDebug s, const ComplexMatrix& m) {
    s << ComplexMatrix_toString(m);
    return s;
}
