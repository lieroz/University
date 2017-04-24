#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <QGraphicsScene>

#include "scene/scene.hpp"
#include "primitives/matrix4x4.hpp"

class draw_manager {
    public:
        draw_manager() = default;
        draw_manager(draw_manager&) = delete;
        draw_manager(const draw_manager&) = delete;
        ~draw_manager() = default;

        void draw(scene& sc, QGraphicsScene*& g_sc, camera* obj) {
            for (vector<scene_object*>::iterator iter = sc.scene_objects.begin(); iter != sc.scene_objects.end(); ++iter) {

                if ((*iter)->visible()) {
                    model* m = reinterpret_cast<model*>(*iter);
                    matrix4x4<double> mtx = obj->get_view_matrix();

                    for (size_t i = 0; i < m->lines.size(); ++i) {
                        point3d<double> p1 = mtx * m->lines.at(i).get_first();
                        point3d<double> p2 = mtx * m->lines.at(i).get_second();
                        g_sc->addLine(p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y());
                    }
                }
            }
        }
};

#endif // DRAW_MANAGER_HPP
