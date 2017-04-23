#include "model.hpp"

model::model(const std::string& name, const vector<pair<point3d<double>, point3d<double>>>& lines,
             const vector<point3d<double>>& points) : name(name), lines(lines), points(points) {
    this->set_up_center();
}

model::model(const model& other)
    : visible_object(), name(other.name), lines(other.lines), points(other.points), center(other.center) {

}

const point3d<double>& model::get_center() const {
    return this->center;
}

void model::set_center(const point3d<double>& center) {
    this->center = center;
}

void model::set_up_center() {
    vector<point3d<double>>::const_iterator iter = this->points.cbegin();
    double min_x = (*iter).get_x(), max_x = (*iter).get_x();
    double min_y = (*iter).get_y(), max_y = (*iter).get_y();
    double min_z = (*iter).get_z(), max_z = (*iter).get_z();

    for (++iter; iter != this->points.cend(); ++iter) {

        if ((*iter).get_x() < min_x) {
            min_x = (*iter).get_x();
        }

        if ((*iter).get_x() > max_x) {
            max_x = (*iter).get_x();
        }

        if ((*iter).get_y() < min_y) {
            min_y = (*iter).get_y();
        }

        if ((*iter).get_y() > max_y) {
            max_y = (*iter).get_y();
        }

        if ((*iter).get_z() < min_z) {
            min_z = (*iter).get_z();
        }

        if ((*iter).get_z() > max_z) {
            max_z = (*iter).get_z();
        }
    }

    this->center = point3d<double>((min_x + max_x) / 2., (min_y + max_y) / 2., (min_z + max_z) / 2.);
}
