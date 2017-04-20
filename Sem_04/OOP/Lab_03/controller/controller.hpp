#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "scene/scene.hpp"
#include "model_view/model_view.hpp"
#include "managers/camera_manager.hpp"
#include "managers/model_manager.hpp"
#include "managers/draw_manager.hpp"
#include "managers/upload_manager.hpp"

class controller {
    public:
        static controller* instance() {
            return new controller();
        }

        ~controller() = default;

        void upload_model(const std::string& file_name) {
            this->__model_view.add_view(this->__upload_manager.upload_model(file_name));
        }

    protected:
        controller() = default;
        controller(controller&) = delete;
        controller(const controller&) = delete;

    private:
        scene __scene;
        model_view __model_view;
        camera_manager __camera_manager;
        model_manager __model_manager;
        draw_manager __draw_manager;
        upload_manager __upload_manager;
};

#endif // CONTROLLER_HPP
