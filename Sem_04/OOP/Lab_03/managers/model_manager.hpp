#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include "abstract_manager.hpp"

class model_manager : public abstract_manager {
    public:
        model_manager() = default;
        model_manager(model_manager&) = delete;
        model_manager(const model_manager&) = delete;
        ~model_manager() = default;
};

#endif // MODEL_MANAGER_HPP
