#include "state.hpp"

State State_probabilities(const State& t) {
    State s(ComplexVector_normalize(t));
    for (int i = 0; i < s._length; i += 1) {
        Complex_set(s.at(i), Complex(Real_square(Complex_modulus(*s.at(i)))));
    }
    return s;
}

Complex State_transitionAmpltitude(const State& fromKet, const State& toKet) {
    return ComplexVector_innerProduct(fromKet, toKet);
}

