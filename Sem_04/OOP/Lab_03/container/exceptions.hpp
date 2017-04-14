#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

class base_exception : public std::exception {
    protected:
        std::string message;

    public:
        explicit base_exception() = default;

        explicit base_exception(const char* message) {
            this->message = message;
        }

        explicit base_exception(std::string& message) {
            this->message = message;
        }
};

class bad_memory_allocation_exception : public base_exception {
    public:
        explicit bad_memory_allocation_exception() = default;

        explicit bad_memory_allocation_exception(const char* message)
                : base_exception(message) {
        }

        explicit bad_memory_allocation_exception(std::string& message)
                : base_exception(message) {
        }

        virtual const char* what() const noexcept {
            return message.empty() ? "Memory allocation error!" : message.c_str();
        }
};

class out_of_range_exception : public base_exception {
    public:
        explicit out_of_range_exception() = default;

        explicit out_of_range_exception(const char* message)
                : base_exception(message) {
        }

        explicit out_of_range_exception(std::string& message)
                : base_exception(message) {
        }

        virtual const char* what() const noexcept {
            return message.empty() ? "Accessed position is out of range!" : message.c_str();
        }
};

#endif // EXCEPTIONS_HPP
