#include "scene.hpp"

scene* scene::instance() {
    return new scene();
}

bool scene::add(model* m) {
    try {
        this->models.push_back(m);

    } catch (base_container_exception& ex) {
        return false;
    }

    return true;
}

bool scene::remove() {
    try {
        this->models.push_back(m);

    } catch (base_container_exception& ex) {
        return false;
    }

    return true;
}

bool scene::insert(size_t pos, model* m) {
    try {
        this->models.insert(pos, m);

    } catch (base_container_exception& ex) {
        return false;
    }

    return true;
}

bool scene::erase(size_t pos) {
    try {
        this->models.erase(pos);

    } catch (base_container_exception& ex) {
        return false;
    }

    return true;
}
