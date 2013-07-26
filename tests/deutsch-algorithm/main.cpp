#include <QDebug>

#include "complexmatrix.hpp"
#include "debug.hpp"
#include "state.hpp"

using namespace std;

bool f1(bool x) {return  x;}
bool f2(bool x) {return !x;}
bool f3(bool)   {return  0;}
bool f4(bool)   {return  1;}

int main(int argc, char **args) {

    (void) argc; (void) args;

    State s0(State_Qubit_Zero);
    State s1(State_Qubit_One);

    ComplexMatrix H(ComplexMatrix_Hadamard);
    ComplexMatrix HxH(ComplexMatrix_tensorProduct(H, H));

    State Hs0xHs1(ComplexVector_tensorProduct(ComplexMatrix_mul(H, s0), ComplexMatrix_mul(H, s1)));

    // use HxH instead if HxI (book page 176) to make the lower bit |1> and ease extracting the top bit

    State t1(ComplexMatrix_mul(HxH, ComplexMatrix_mul(ComplexMatrix_controlledNot(f1), Hs0xHs1)));
    State t2(ComplexMatrix_mul(HxH, ComplexMatrix_mul(ComplexMatrix_controlledNot(f2), Hs0xHs1)));
    State t3(ComplexMatrix_mul(HxH, ComplexMatrix_mul(ComplexMatrix_controlledNot(f3), Hs0xHs1)));
    State t4(ComplexMatrix_mul(HxH, ComplexMatrix_mul(ComplexMatrix_controlledNot(f4), Hs0xHs1)));

    // use only the upper qubit, lower one is always |1>

    State u1(2); Complex_set(u1.at(0), *t1.at(1)); Complex_set(u1.at(1), *t1.at(3));
    State u2(2); Complex_set(u2.at(0), *t2.at(1)); Complex_set(u2.at(1), *t2.at(3));
    State u3(2); Complex_set(u3.at(0), *t3.at(1)); Complex_set(u3.at(1), *t3.at(3));
    State u4(2); Complex_set(u4.at(0), *t4.at(1)); Complex_set(u4.at(1), *t4.at(3));

    qDebug() << "f(x)=    x" << u1;
    qDebug() << "f(x)=not x" << u2;
    qDebug() << "f(x)=    0" << u3;
    qDebug() << "f(x)=    1" << u4;

    ASSERT(ComplexVector_isEqual(u1, State_Qubit_One));
    ASSERT(ComplexVector_isEqual(u2, ComplexVector_mul(State_Qubit_One, Complex_MinusOne)));
    ASSERT(ComplexVector_isEqual(u3, State_Qubit_Zero));
    ASSERT(ComplexVector_isEqual(u4, ComplexVector_mul(State_Qubit_Zero, Complex_MinusOne)));

    return 0;
}

