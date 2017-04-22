#include "transformation_interface.hpp"

transformation_interface::transformation_interface()
    : matrix<double>(4, 4) {
    this->reset_matrix();
}

void transformation_interface::reset_matrix() {
    *(reinterpret_cast<matrix<double>*>(this)) = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}
