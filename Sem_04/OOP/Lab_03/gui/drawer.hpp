#ifndef DRAWER_HPP
#define DRAWER_HPP

#include <QGraphicsScene>

#include "primitives/point3d.hpp"

struct drawer {
        drawer(QGraphicsScene*& graphics_scene) : graphics_scene(graphics_scene) {}

        void operator()(const point3d<double>& p1, const point3d<double>& p2) {
            this->graphics_scene->addLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
        }

    private:
        QGraphicsScene* graphics_scene;
};

#endif // DRAWER_HPP
