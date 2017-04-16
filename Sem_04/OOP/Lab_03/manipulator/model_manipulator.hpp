#ifndef MODEL_MANIPULATOR_HPP
#define MODEL_MANIPULATOR_HPP

#include "base_manipulator.hpp"

class model_manipulator : public base_manipulator {
    public:
        explicit model_manipulator(scene* s = 0);
        virtual ~model_manipulator();

        void perform_action(command*) override;
};

#endif // MODEL_MANIPULATOR_HPP
