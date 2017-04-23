#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>

#include "visible_object.hpp"
#include "containers/vector/vector.hpp"
#include "containers/pair/pair.hpp"
#include "primitives/point3d.hpp"

class model : public visible_object {
    public:
        explicit model() = default;
        explicit model(const std::string&, const vector<pair<point3d<double>, point3d<double>>>&,
                       const vector<point3d<double>>&);
        model(const model&);
        virtual ~model() = default;

        const point3d<double>& get_center() const;
        void set_center(const point3d<double>&);

        friend class model_transformations;
        friend class draw_manager;

    protected:
        void set_up_center();

    private:
        std::string name;
        vector<point3d<double>> points;
        vector<pair<point3d<double>, point3d<double>>> lines;
        point3d<double> center;
};

#endif // MODEL_HPP
