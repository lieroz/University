#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "abstract_manager.hpp"

class draw_manager : public abstract_manager {
    public:
        draw_manager() = default;
        draw_manager(draw_manager&) = delete;
        draw_manager(const draw_manager&) = delete;
        ~draw_manager() = default;
};

#endif // DRAW_MANAGER_HPP
