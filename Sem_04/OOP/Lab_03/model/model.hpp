#ifndef MODEL_HPP
#define MODEL_HPP

#include "../container/vector/vector.hpp"
#include "../container/pair/pair.hpp"
#include "../primitives/point3d.hpp"

class model {
    public:
        explicit model(vector<pair<size_t, point3d>>&, vector<pair<size_t, vector<size_t>>>&);
        model(const model&);
        ~model() = default;

        vector<pair<size_t, point3d>>& get_points();
        vector<pair<size_t, vector<size_t>>>& get_links();

        static const get_model_id() const;

    private:
        vector<pair<size_t, point3d>> points;
        vector<pair<size_t, vector<size_t>>> links;

        static size_t model_id;
};

#endif // MODEL_HPP
