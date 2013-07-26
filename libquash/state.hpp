#ifndef STATE_HPP
#define STATE_HPP

#include "complexvector.hpp"

typedef ComplexVector State;

State State_probabilities(const State& s);

Complex State_transitionAmpltitude(const State& fromKet, const State& toKet);

const State State_Qubit_One = ComplexVector_fromString("[0, 1]");
const State State_Qubit_Zero = ComplexVector_fromString("[1, 0]");

#endif
