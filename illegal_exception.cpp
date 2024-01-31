#include "illegal_exception.hpp"

const char* illegal_exception::what () const noexcept {
        return "illegal argument";
}
