#ifndef BASE_MANIPULATOR_HPP
#define BASE_MANIPULATOR_HPP

#include "../scene/scene.hpp"
#include "../command/command.hpp"

class base_manipulator {
    public:
        explicit base_manipulator(scene* s = 0);
        virtual ~base_manipulator();

        virtual void perform_action(command*) = 0;

    protected:
        scene* s;
};

#endif // BASE_MANIPULATOR_HPP
