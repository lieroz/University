#ifndef SCENE_HPP
#define SCENE_HPP

#include "../container/vector/vector.hpp"
#include "../model/model.hpp"

class scene {
    public:
        static scene* instance();

        bool add(model*);
        bool remove();

        bool insert(size_t, model*);
        bool erase(size_t);

    protected:
        explicit scene() = default;
        scene(const scene&) = delete;
        scene(scene&&) = delete;
        ~scene() = default;

    private:
        vector<model*> models;
};

#endif // SCENE_HPP
