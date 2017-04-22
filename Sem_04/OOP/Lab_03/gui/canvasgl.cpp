#include "canvasgl.hpp"
#include "controller/controller.hpp"
#include "commands/command.hpp"

#include <QApplication>
#include <QKeyEvent>

CanvasGL::CanvasGL(QWidget* parent)
    : QGLWidget(parent), m_aspectRatio(1.0f) {
    commands::upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
    f.execute_command(c1);
    commands::add_model c3(0);
    f.execute_command(c3);
    f.execute_command(c3);
}

void CanvasGL::initializeGL() {
    glClearColor(213.0f, 213.0f, 213.0f, 1.0f);
}

void CanvasGL::resizeGL(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    double range = 1000.0;
    m_aspectRatio = double(w) / double(h);

    if (w <= h) {
        glOrtho(-range, range, -range / m_aspectRatio, range / m_aspectRatio, range, -range);

    } else {
        glOrtho(-range * m_aspectRatio, range * m_aspectRatio, -range, range, range, -range);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CanvasGL::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );

    glColor3f(1.0f, 0.0f, 243.0f);

    glPushMatrix();

    glLineWidth(3);

    commands::draw c;
    f.execute_command(c);

    glPopMatrix();
}

void CanvasGL::keyPressEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Escape) {
        QCoreApplication::instance()->quit();

    } else if (e->key() == Qt::Key_Left) {
        commands::rotate_model_OY rot(-2 * M_PI / 180, 0);
        f.execute_command(rot);
        updateGL();

    } else if (e->key() == Qt::Key_Right) {
        commands::rotate_model_OY rot(2 * M_PI / 180, 0);
        f.execute_command(rot);
        updateGL();

    } else if (e->key() == Qt::Key_Up) {
        commands::rotate_model_OX rot(-2 * M_PI / 180, 0);
        f.execute_command(rot);
        updateGL();

    } else if (e->key() == Qt::Key_Down) {
        commands::rotate_model_OX rot(2 * M_PI / 180, 0);
        f.execute_command(rot);
        updateGL();
    } else if (e->key() == Qt::Key_D) {
        point3d<double> point(2, 0, 0);
        commands::move mv(point, -1);
        f.execute_command(mv);
        updateGL();

    } else if (e->key() == Qt::Key_A) {
        point3d<double> point(-2, 0, 0);
        commands::move mv(point, -1);
        f.execute_command(mv);
        updateGL();

    } else if (e->key() == Qt::Key_W) {
        point3d<double> point(0, 2, 0);
        commands::move mv(point, -1);
        f.execute_command(mv);
        updateGL();

    } else if (e->key() == Qt::Key_S) {
        point3d<double> point(0, -2, 0);
        commands::move mv(point, -1);
        f.execute_command(mv);
        updateGL();

    } else if (e->key() == Qt::Key_5) {
        point3d<double> point(0, 0, 2);
        commands::move mv(point, -1);
        f.execute_command(mv);
        updateGL();
    }
}
