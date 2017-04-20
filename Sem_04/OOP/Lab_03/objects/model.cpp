#include "model.hpp"

model::model(const std::string& name, const vector<pair<int, point3d<double>>>& points,
             const vector<pair<int, vector<int>>>& links) : name(name), points(points), links(links) {
    this->set_up_center();
}

model::model(const model& other) : visible_object(), name(other.name), points(other.points), links(other.links), center(other.center) {

}

void model::transform(abstract_transformations*& transformation) {

}

const point3d<double>& model::get_center() const {
    return this->center;
}

void model::set_center(const point3d<double>& center) {
    this->center = center;
}

void model::set_up_center() {
    vector<pair<int, point3d<double>>>::const_iterator iter = this->points.cbegin();
    double min_x = (*iter).get_second().get_x(), max_x = (*iter).get_second().get_x();
    double min_y = (*iter).get_second().get_y(), max_y = (*iter).get_second().get_y();
    double min_z = (*iter).get_second().get_z(), max_z = (*iter).get_second().get_z();

    for (++iter; iter != this->points.cend(); ++iter) {

        if ((*iter).get_second().get_x() < min_x) {
            min_x = (*iter).get_second().get_x();

        }

        if ((*iter).get_second().get_x() > max_x) {
            max_x = (*iter).get_second().get_x();
        }

        if ((*iter).get_second().get_y() < min_y) {
            min_y = (*iter).get_second().get_y();

        }

        if ((*iter).get_second().get_y() > max_y) {
            max_y = (*iter).get_second().get_y();
        }

        if ((*iter).get_second().get_z() < min_z) {
            min_z = (*iter).get_second().get_z();

        }

        if ((*iter).get_second().get_z() > max_z) {
            max_z = (*iter).get_second().get_z();
        }
    }

    this->center = point3d<double>((min_x + max_x) / 2., (min_y + max_y) / 2., (min_z + max_z) / 2.);
}
