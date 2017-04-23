#include "canvasgl.hpp"
#include "controller/controller.hpp"
#include "commands/command.hpp"

#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>

CanvasGL::CanvasGL(QWidget* parent)
    : QGLWidget(parent) {
    commands::upload_view c1("/home/lieroz/University/Sem_04/OOP/Lab_03/DATA/cube.json");
    f.execute_command(c1);
    commands::add_model c3(0);
    f.execute_command(c3);
}

void CanvasGL::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void CanvasGL::resizeGL(int w, int h) {
    if (h == 0) {
        h = 1;
    }

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const double aspect_ratio = static_cast<double>(w) / static_cast<double>(h);
    const int screen_width = QApplication::desktop()->screenGeometry().width();
    const int screen_height = QApplication::desktop()->screenGeometry().height();

    if (screen_width <= screen_height) {
        glOrtho(-screen_width, screen_width, -screen_width / aspect_ratio,
                screen_width / aspect_ratio, screen_width * 2, -screen_width * 2);

    } else {
        glOrtho(-screen_height * aspect_ratio, screen_height * aspect_ratio, -screen_height,
                screen_height, screen_height * 2, -screen_height * 2);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CanvasGL::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f(0.0f, 255.0f, 0.0f);
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
        commands::rotate_model_OY comm(-2 * M_PI / 180, 0);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_Right) {
        commands::rotate_model_OY comm(2 * M_PI / 180, 0);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_Up) {
        commands::rotate_model_OX comm(-2 * M_PI / 180, 0);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_Down) {
        commands::rotate_model_OX comm(2 * M_PI / 180, 0);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_PageUp) {
        commands::rotate_model_OZ comm(-2 * M_PI / 180, 0);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_PageDown) {
        commands::rotate_model_OZ rot(2 * M_PI / 180, 0);
        f.execute_command(rot);
        updateGL();

    } else if (e->key() == Qt::Key_D) {
        point3d<double> point(5, 0, 0);
        commands::move comm(point, -1);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_A) {
        point3d<double> point(-5, 0, 0);
        commands::move comm(point, -1);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_W) {
        point3d<double> point(0, 5, 0);
        commands::move comm(point, -1);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_S) {
        point3d<double> point(0, -5, 0);
        commands::move comm(point, -1);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_Plus) {
        commands::scale comm(2, -1);
        f.execute_command(comm);
        updateGL();

    } else if (e->key() == Qt::Key_Minus) {
        commands::scale comm(0.5, -1);
        f.execute_command(comm);
        updateGL();
    }
}
