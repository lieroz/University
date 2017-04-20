#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "invisible_object.hpp"

class camera : public invisible_object {
    public:
        camera() = default;
        ~camera() = default;

        void transform(abstract_transformations*&);
};

#endif // CAMERA_HPP
