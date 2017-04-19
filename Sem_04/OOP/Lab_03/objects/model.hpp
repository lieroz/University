#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>

#include "visible_object.hpp"
#include "containers/vector/vector.hpp"
#include "containers/pair/pair.hpp"
#include "primitives/point3d.hpp"

class model : public visible_object {
    public:
        explicit model(const std::string&, const vector<pair<int, point3d<double>>>&, const vector<pair<int, vector<int>>>&);
        model(const model&);
        virtual ~model() = default;

        void transform();

        const point3d<double>& get_center() const;
        void set_center(const point3d<double>&);

    protected:
        void set_up_center();

    private:
        std::string name;
        vector<pair<int, point3d<double>>> points;
        vector<pair<int, vector<int>>> links;
        point3d<double> center;
};

#endif // MODEL_HPP
