#ifndef MYCANVAS_HPP
#define MYCANVAS_HPP

#include <QGraphicsView>
#include <QMouseEvent>
#include <QEvent>

class MyCanvas : public QGraphicsView {
        Q_OBJECT

    public:
        using QGraphicsView::QGraphicsView;

        double x, y;

        virtual void mouseMoveEvent(QMouseEvent*) override;
        virtual void mousePressEvent(QMouseEvent*) override;
        virtual void leaveEvent(QEvent*) override;

    signals:
        void mousePressed();
        void mousePosition();
        void mouseLeft();
};

#endif // MYCANVAS_HPP
