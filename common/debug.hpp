#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>

#define ASSERT(expression) \
    if ((expression) == false) { \
        std::cerr << "\e[0;31m\033[1m" \
                << "ASSERT" \
                << "\033[0m\e[0;30m" \
                << " in " << __FILE__ << ":" << __LINE__ \
                << ": \"" << #expression << "\"" << std::endl; \
        std::abort(); \
    }

#ifdef DEBUG
#   define DEBUG_ASSERT(expression) ASSERT(expression)
#else
#   define DEBUG_ASSERT(expression)
#endif

#endif
