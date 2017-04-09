#include "mycanvas.hpp"

void MyCanvas::mouseMoveEvent(QMouseEvent* event) {
    this->x = event->x();
    this->y = event->y();
    emit this->mousePosition();
}

void MyCanvas::mousePressEvent(QMouseEvent*) {
    emit this->mousePressed();
}

void MyCanvas::leaveEvent(QEvent*) {
    emit this->mouseLeft();
}
