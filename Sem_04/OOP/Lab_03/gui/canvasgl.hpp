#ifndef CANVASGL_HPP
#define CANVASGL_HPP

#include <QGLWidget>
#include "facade/facade.hpp"
#include <QOpenGLWidget>

class CanvasGL : public QGLWidget {
        Q_OBJECT

    public:
        CanvasGL(QWidget* parent = 0);

        virtual void keyPressEvent(QKeyEvent*) override;

    protected:
        virtual void initializeGL();
        virtual void resizeGL(int, int);
        virtual void paintGL();

    private:
        float m_aspectRatio;
        facade f;
};

#endif // CANVASGL_HPP
