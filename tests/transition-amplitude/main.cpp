// programming drill 4.1.1

#include <QDebug>

#include "debug.hpp"
#include "state.hpp"

using namespace std;

int main(int argc, char **args) {

    (void) argc; (void) args;

    State from(ComplexVector_normalize(ComplexVector_fromString("[1, -i]")));
    State to(ComplexVector_normalize(ComplexVector_fromString("[i, 1]")));

    Complex amplitude = State_transitionAmpltitude(from, to);

    qDebug() << from << "---" << amplitude << "--->" << to;

    ASSERT(Complex_isEqual(amplitude, Complex_fromString("-i")));

    return 0;
}

