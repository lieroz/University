#ifndef SCENE_HPP
#define SCENE_HPP

#include "containers/vector/vector.hpp"
#include "objects/model.hpp"

class scene {
    public:
        scene() = default;

        void add_object();
        void remove_object();

    private:
        vector<scene_object*> scene_objects;
};

#endif // SCENE_HPP
