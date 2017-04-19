#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "scene/scene.hpp"
#include "managers/camera_manager.hpp"
#include "managers/model_manager.hpp"
#include "managers/draw_manager.hpp"
#include "managers/upload_manager.hpp"

class controller {
    public:
        static controller* instance();

    protected:
        controller() = default;
        controller(controller&) = delete;
        controller(const controller&) = delete;
        ~controller() = default;

    private:
        scene sc;
        camera_manager cam_mngr;
        model_manager mdl_mngr;
        draw_manager drw_mngr;
        upload_manager upl_mngr;
};

#endif // CONTROLLER_HPP
