#ifndef SCENE_MANIPULATOR_HPP
#define SCENE_MANIPULATOR_HPP

#include "base_manipulator.hpp"

class scene_manipulator : public base_manipulator {
    public:
        explicit scene_manipulator(scene* s = 0);
        virtual ~scene_manipulator();

        void perform_action(command*) override;
};

#endif // SCENE_MANIPULATOR_HPP
