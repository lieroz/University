#ifndef MODEL_VIEW_EXCEPTIONS_HPP
#define MODEL_VIEW_EXCEPTIONS_HPP

#include "base_exception.hpp"

class model_out_of_range_exception : public base_exception {
    public:
        virtual const char* what() const noexcept {
            return "model_view::(model is out of range)!";
        }
};

#endif // MODEL_VIEW_EXCEPTIONS_HPP
