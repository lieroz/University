#ifndef TRANSFORMATIONS_HPP
#define TRANSFORMATIONS_HPP

#include "objects/scene_object.hpp"
#include "transformation_interface.hpp"
#include "containers/vector/vector.hpp"
#include "primitives/point3d.hpp"

class base_transformations {
    public:
        base_transformations(transformation_interface& interface) : transformation_matrix(interface) {}
        base_transformations(base_transformations&) = delete;
        base_transformations(const base_transformations&) = delete;
        virtual ~base_transformations() = default;

        virtual void transform(scene_object*&) = 0;

    protected:
        matrix<double> transformation_matrix = matrix<double>(4, 4);

        const point3d<double>& multiply(const matrix<double>& mtx, point3d<double>& pt) {
            vector<double> vec = pt.to_vector4d();
            vector<double> result = {0, 0, 0, 0};

            for (size_t i = 0; i < 4; ++i) {

                for (size_t j = 0; j < 4; ++j) {
                    result[i] += mtx[i][j] * vec[j];
                }
            }

            pt = point3d<double>(result[0], result[1], result[2]);
            return pt;
        }
};

#endif // TRANSFORMATIONS_HPP
