#ifndef FACADE_HPP
#define FACADE_HPP

#include <string>

#include "controller/controller.hpp"
#include "commands/command.hpp"
#include "exceptions/base_exception.hpp"

class facade {
    public:
        facade() {
            this->__controller = controller::instance();
        }

        facade(facade&) = delete;
        facade(const facade&) = delete;

        ~facade() {
            delete this->__controller;
        }

        bool execute_command(command& c) {
            try {
                c.execute(this->__controller);

            } catch (base_exception& ex) {
                this->exception_message = ex.what();
                return false;
            }

            return true;
        }

        const std::string& recieve_exception_message() const {
            return this->exception_message;
        }

    private:
        std::string exception_message;
        controller* __controller;
};

#endif // FACADE_HPP
