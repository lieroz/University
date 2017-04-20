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

class upload_view : public command {
    public:
        upload_view(const std::string& file_name) : file_name(file_name) {}
        upload_view(upload_view&) = delete;
        upload_view(const upload_view&) = delete;
        ~upload_view() = default;

        virtual void execute(controller*& c) {
            c->upload_view(file_name);
        }

    private:
        std::string file_name;
};

class delete_view : public command {
    public:
        delete_view(size_t view_index) : view_index(view_index) {}
        delete_view(delete_view&) = delete;
        delete_view(const delete_view&) = delete;
        ~delete_view() = default;

        virtual void execute(controller*& c) {
            c->delete_view(this->view_index);
        }

    private:
        size_t view_index;
};

class add_model : public command {
    public:
        add_model(size_t view_index) : view_index(view_index) {}
        add_model(add_model&) = delete;
        add_model(const add_model&) = delete;
        ~add_model() = default;

        virtual void execute(controller*& c) {
            c->add_model(this->view_index);
        }

    private:
        size_t view_index;
};

class remove_model : public command {
    public:
        remove_model(size_t model_index) : model_index(model_index) {}
        remove_model(remove_model&) = delete;
        remove_model(const remove_model&) = delete;
        ~remove_model() = default;

        virtual void execute(controller*& c) {
            c->remove_model(this->model_index);
        }

    private:
        size_t model_index;
};

class add_camera : public command {
    public:
        add_camera() = default;
        add_camera(add_camera&) = delete;
        add_camera(const add_camera&) = delete;
        ~add_camera() = default;

        virtual void execute(controller*& c) {
            c->add_camera();
        }
};

class remove_camera : public command {
    public:
        remove_camera(size_t camera_index) : camera_index(camera_index) {}
        remove_camera(remove_camera&) = delete;
        remove_camera(const remove_camera&) = delete;
        ~remove_camera() = default;

        virtual void execute(controller*& c) {
            c->remove_camera(this->camera_index);
        }

    private:
        size_t camera_index;
};

#endif // COMMAND_HPP
