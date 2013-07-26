#include "state.hpp"

State State_probabilities(const State& t) {
    State s(ComplexVector_normalize(t));
    for (int i = 0; i < s._length; i += 1) {
        Complex_set(ComplexVector_at(&s, i), Complex(Real_square(Complex_modulus(s[i]))));
    }
    return s;
}

