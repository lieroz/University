#include "model.hpp"

size_t model::model_id = 0;

model::model(const vector<pair<size_t, point3d>>& points, const vector<pair<size_t, vector<size_t>>>& links) {
    ++model_id;
    this->points = points;
    this->links = links;
}

model::model(const model& other) {
    ++model_id;
    this->points = other.points;
    this->links = other.links;
}

vector<pair<size_t, point3d>>& model::get_points() {
    return this->points;
}

vector<pair<size_t, vector<size_t>>>& model::get_links() {
    return this->links;
}

const model::get_model_id() const {
    return model_id;
}
