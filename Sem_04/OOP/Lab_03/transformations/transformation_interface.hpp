#ifndef TRANSFORMATION_INTERFACE_HPP
#define TRANSFORMATION_INTERFACE_HPP

#include "containers/matrix/matrix.hpp"

class transformation_interface : public matrix<double> {
    public:
        transformation_interface();
        transformation_interface(transformation_interface&) = delete;
        transformation_interface(const transformation_interface&) = delete;
        ~transformation_interface() = default;

    protected:
        void reset_matrix();
};

#endif // TRANSFORMATION_INTERFACE_HPP
