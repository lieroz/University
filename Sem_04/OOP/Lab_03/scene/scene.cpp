#include "scene.hpp"

void scene::transform(base_transformations* transformation) {
    for (vector<scene_object*>::iterator iter = scene_objects.begin(); iter != scene_objects.end(); ++iter) {
        transformation->transform(*iter);
    }
}

bool scene::visible() {
    return true;
}

void scene::add_model(scene_object* object) {
    this->scene_objects.push_back(reinterpret_cast<model*>(object));
    ++this->model_count;
}

void scene::remove_model(size_t index) {
    if (index < this->model_count) {
        size_t count = 0;
        size_t i = 0;

        for (; i < this->scene_objects.size(); ++i) {

            if (this->scene_objects[i]->visible()) {
                ++count;

                if (count - 1 == index) {
                    break;
                }
            }
        }

        this->scene_objects.erase(i);
        --this->model_count;

    } else {
        throw scene_out_of_range_exception("scene::(no model on such position)!");
    }
}

void scene::add_camera(scene_object* object) {
    this->scene_objects.push_back(reinterpret_cast<camera*>(object));
    ++this->camera_count;
}

void scene::remove_camera(size_t index) {
    if (index < this->camera_count) {
        size_t count = 0;
        size_t i = 0;

        for (; i < this->scene_objects.size(); ++i) {

            if (!this->scene_objects[i]->visible()) {
                ++count;

                if (count - 1 == index) {
                    break;
                }
            }
        }

        this->scene_objects.erase(i);
        --this->camera_count;

    } else {
        throw scene_out_of_range_exception("scene::(no camera on such position)!");
    }
}

scene_object*& scene::get_model(size_t index) {
    if (index < this->model_count) {
        size_t count = 0;
        size_t i = 0;

        for (; i < this->scene_objects.size(); ++i) {

            if (this->scene_objects[i]->visible()) {
                ++count;

                if (count - 1 == index) {
                    break;
                }
            }
        }

        return this->scene_objects[i];

    } else {
        throw scene_out_of_range_exception("scene::(no object on such position)!");
    }
}

scene_object*& scene::get_camera(size_t index) {
    if (index < this->camera_count) {
        size_t count = 0;
        size_t i = 0;

        for (; i < this->scene_objects.size(); ++i) {

            if (!this->scene_objects[i]->visible()) {
                ++count;

                if (count - 1 == index) {
                    break;
                }
            }
        }

        return this->scene_objects[i];

    } else {
        throw scene_out_of_range_exception("scene::(no camera on such position)!");
    }
}
