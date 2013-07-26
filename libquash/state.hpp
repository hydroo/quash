#ifndef STATE_HPP
#define STATE_HPP

#include "complexvector.hpp"

typedef ComplexVector State;

State State_probabilities(const State& s);

Complex State_transitionAmpltitude(const State& fromKet, const State& toKet);

#endif
