#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "controller/controller.hpp"

class command {
    public:
        command() = default;
        command(command&) = delete;
        command(const command&) = delete;
        ~command() = default;

        virtual void execute(controller*&) = 0;
};

class load_model : public command {
    public:
        load_model(const std::string& file_name) : file_name(file_name) {}
        load_model(load_model&) = delete;
        load_model(const load_model&) = delete;
        ~load_model() = default;

        virtual void execute(controller*& c) {
            c->upload_model(file_name);
        }

    private:
        std::string file_name;
};

#endif // COMMAND_HPP
