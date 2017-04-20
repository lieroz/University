#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include "abstract_manager.hpp"

class camera_manager : public abstract_manager {
    public:
        camera_manager() = default;
        camera_manager(camera_manager&) = delete;
        camera_manager(const camera_manager&) = delete;
        ~camera_manager() = default;
};

#endif // CAMERA_MANAGER_HPP
