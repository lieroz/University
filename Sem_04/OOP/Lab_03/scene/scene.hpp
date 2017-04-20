#ifndef SCENE_HPP
#define SCENE_HPP

#include "exceptions/scene_exceptions.hpp"
#include "containers/vector/vector.hpp"
#include "objects/model.hpp"
#include "objects/camera.hpp"

class scene {
    public:
        scene() = default;

        void add_model(scene_object* object) {
            this->scene_objects.push_back(reinterpret_cast<model*>(object));
            ++this->model_count;
        }

        void remove_model(size_t index) {
            if (index < this->model_count) {
                size_t count = 0;
                size_t i = 0;

                for (; i < this->scene_objects.size(), count < index; ++i) {

                    if (this->scene_objects[i]->visible()) {
                        ++count;
                    }
                }

                this->scene_objects.erase(i);
                --this->model_count;

            } else {
                throw scene_out_of_range_exception("scene::(no model on such position)!");
            }
        }

        void add_camera(scene_object* object) {
            this->scene_objects.push_back(reinterpret_cast<camera*>(object));
            ++this->camera_count;
        }

        void remove_camera(size_t index) {
            if (index < this->camera_count) {
                size_t count = 0;
                size_t i = 0;

                for (; i < this->scene_objects.size(), count < index; ++i) {

                    if (!this->scene_objects[i]->visible()) {
                        ++count;
                    }
                }

                this->scene_objects.erase(i);
                --this->camera_count;

            } else {
                throw scene_out_of_range_exception("scene::(no camera on such position)!");
            }
        }

    private:
        size_t camera_count;
        size_t model_count;
        vector<scene_object*> scene_objects;
};

#endif // SCENE_HPP
