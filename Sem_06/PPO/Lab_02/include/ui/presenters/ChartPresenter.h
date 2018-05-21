//
// Created by lieroz on 21.05.18.
//

#ifndef CHARTPRESENTER_H
#define CHARTPRESENTER_H

#include <QChartView>

#include <data/models/Route.h>

QT_CHARTS_USE_NAMESPACE

class ChartPresenter : public QChartView
{
public:
    ChartPresenter(QWidget *parent = nullptr);

    void setData(QSharedPointer<Route> route);

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool m_isTouching;
};

#endif // CHARTPRESENTER_H
