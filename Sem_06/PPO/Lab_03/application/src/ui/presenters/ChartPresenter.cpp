//
// Created by lieroz on 21.05.18.
//

#include <QLineSeries>
#include <QVXYModelMapper>
#include <QPanGesture>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>

#include <ui/presenters/ChartPresenter.h>

ChartPresenter::ChartPresenter(QWidget *parent)
    : QChartView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setRubberBand(QChartView::RectangleRubberBand);
}

void ChartPresenter::setData(QSharedPointer<Route> route)
{
    QLineSeries *series = new QLineSeries(this);
    qint32 distance = 0;

    for (auto i = 0; i < route->getPath().count(); ++i) {
        QPointF point;
        auto curr = route->getCoordinate(i);

        if (i == 0) {
            point.setX(0);
        } else {
            auto prev = route->getCoordinate(i - 1);
            distance += prev->distanceTo(*curr) * 1000;
            point.setX(distance);
        }

        point.setY(curr->getAltitude());
        *series << point;
    }

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Route altitude chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->createDefaultAxes();

    setChart(chart);
}

bool ChartPresenter::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        m_isTouching = true;
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void ChartPresenter::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching) {
        return;
    }
    QChartView::mousePressEvent(event);
}

void ChartPresenter::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching) {
        return;
    }
    QChartView::mouseMoveEvent(event);
}

void ChartPresenter::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching) {
        m_isTouching = false;
    }
    chart()->setAnimationOptions(QChart::SeriesAnimations);
    QChartView::mouseReleaseEvent(event);
}

void ChartPresenter::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
