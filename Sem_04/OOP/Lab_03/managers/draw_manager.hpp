#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <QGraphicsScene>

#include "scene/scene.hpp"

class draw_manager {
    public:
        draw_manager() = default;
        draw_manager(draw_manager&) = delete;
        draw_manager(const draw_manager&) = delete;
        ~draw_manager() = default;

        void draw(scene& sc, QGraphicsScene*& g_sc) {
            for (vector<scene_object*>::iterator iter = sc.scene_objects.begin(); iter != sc.scene_objects.end(); ++iter) {

                if ((*iter)->visible()) {
                    model* m = reinterpret_cast<model*>(*iter);

                    for (size_t i = 0; i < m->lines.size(); ++i) {
                        g_sc->addLine(m->lines.at(i).get_first().get_x(), m->lines.at(i).get_first().get_y(),
                                      m->lines.at(i).get_second().get_x(), m->lines.at(i).get_second().get_y());
                    }
                }
            }
        }
};

#endif // DRAW_MANAGER_HPP
