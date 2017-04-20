#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include "transformations/abstract_transformations.hpp"

class scene_object {
    public:
        explicit scene_object() = default;
        scene_object(scene_object&) = delete;
        scene_object(const scene_object&) = delete;
        virtual ~scene_object() = default;

        virtual void transform(abstract_transformations*&) = 0;
        virtual bool visible() = 0;
};

#endif // SCENE_OBJECT_HPP
