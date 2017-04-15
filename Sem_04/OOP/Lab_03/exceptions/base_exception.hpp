#ifndef BASE_EXCEPTION_HPP
#define BASE_EXCEPTION_HPP

#include <exception>

class base_exception : public std::exception {
    public:
        virtual const char* what() const noexcept {
            return "base_exception";
        }
};

#endif // BASE_EXCEPTION_HPP
