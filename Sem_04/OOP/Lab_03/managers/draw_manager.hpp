#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include <QGLWidget>

#include "scene/scene.hpp"

class draw_manager {
    public:
        draw_manager() = default;
        draw_manager(draw_manager&) = delete;
        draw_manager(const draw_manager&) = delete;
        ~draw_manager() = default;

        void draw_line(model*& m, size_t i, size_t k) {
            for (size_t j = 0; j < m->links[i].get_second().size(); ++j) {

                for (size_t w = 0; w < m->points.size(); ++w) {

                    if (m->links[i].get_second()[j] == m->points[w].get_first()) {
                        glBegin(GL_LINE_STRIP);
                        glVertex3d(m->points.at(k).get_second().get_x(), m->points.at(k).get_second().get_y(),
                                   m->points.at(k).get_second().get_z());
                        glVertex3d(m->points.at(w).get_second().get_x(), m->points.at(w).get_second().get_y(),
                                   m->points.at(w).get_second().get_z());
                        glEnd();
                    }
                }
            }
        }

        void draw_model(model*& m) {
            for (size_t i = 0; i < m->links.size(); ++i) {

                for (size_t k = 0; k < m->points.size(); ++k) {

                    if (m->links[i].get_first() == m->points[k].get_first()) {
                        this->draw_line(m, i, k);
                    }
                }
            }
        }

        void draw(scene& sc) {
            for (vector<scene_object*>::iterator iter = sc.scene_objects.begin(); iter != sc.scene_objects.end(); ++iter) {

                if ((*iter)->visible()) {
                    model* m = reinterpret_cast<model*>(*iter);
                    this->draw_model(m);
                }
            }
        }
};

#endif // DRAW_MANAGER_HPP
