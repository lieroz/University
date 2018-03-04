#include <commands.h>

AddRouteCommand::AddRouteCommand(const Route &route,
                                 const std::function<void (Route &)> &redoFunc,
                                 const std::function<void ()> &undoFunc,
                                 QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_route = route;
    m_redoFunc = redoFunc;
    m_undoFunc = undoFunc;
}

void AddRouteCommand::undo()
{
    m_undoFunc();
}

void AddRouteCommand::redo()
{
    m_redoFunc(m_route);
}

/******************************************************************************
** DeleteRouteCommand
*/

DeleteRouteCommand::DeleteRouteCommand(const Route &route,
                                       const std::function<void ()> &redoFunc,
                                       const std::function<void (Route &)> &undoFunc,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_route = route;
    m_redoFunc = redoFunc;
    m_undoFunc = undoFunc;
}

void DeleteRouteCommand::undo()
{
    m_undoFunc(m_route);
}

void DeleteRouteCommand::redo()
{
    m_redoFunc();
}

/******************************************************************************
** AddPointCommand
*/

AddPointCommand::AddPointCommand(qint32 routeIndex, qint32 pointIndex,
                                 QTableWidget *widget, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_widget = widget;
}

void AddPointCommand::undo()
{
    m_widget->removeRow(m_pointIndex);
    RouteStore::instance()->getRoute(m_routeIndex).removeCoordinate(m_pointIndex);
}

void AddPointCommand::redo()
{
    m_widget->insertRow(m_pointIndex);
    m_widget->setItem(m_pointIndex, 0, new QTableWidgetItem(QString::number(0)));
    m_widget->setItem(m_pointIndex, 1, new QTableWidgetItem(QString::number(0)));
    RouteStore::instance()->getRoute(m_routeIndex).appendCoordinate(QGeoCoordinate(0, 0));
}

/******************************************************************************
** ModifyPointCommand
*/

ModifyPointCommand::ModifyPointCommand(qint32 routeIndex, qint32 pointIndex, MapViewProxy *proxy,
                                       QTableWidget *routeWidget, QTableWidget *pointWidget,
                                       const QGeoCoordinate &point, const QGeoCoordinate &oldPoint,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_proxy = proxy;
    m_routeWidget = routeWidget;
    m_pointWidget = pointWidget;
    m_point = point;
    m_oldPoint = oldPoint;
}

void ModifyPointCommand::undo()
{
    Route &route = RouteStore::instance()->getRoute(m_routeIndex);
    route.replaceCoordinate(m_pointIndex, m_oldPoint);
    route.updateLength();
    m_pointWidget->item(m_pointIndex, 0)->setText(QString::number(m_oldPoint.latitude()));
    m_pointWidget->item(m_pointIndex, 1)->setText(QString::number(m_oldPoint.longitude()));
    m_routeWidget->item(m_routeIndex, 1)->setText(QString::number(route.getLength() / 1000));
    emit m_proxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

void ModifyPointCommand::redo()
{
    Route &route = RouteStore::instance()->getRoute(m_routeIndex);
    route.replaceCoordinate(m_pointIndex, m_point);
    route.updateLength();
    m_pointWidget->item(m_pointIndex, 0)->setText(QString::number(m_point.latitude()));
    m_pointWidget->item(m_pointIndex, 1)->setText(QString::number(m_point.longitude()));
    m_routeWidget->item(m_routeIndex, 1)->setText(QString::number(route.getLength() / 1000));
    emit m_proxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

/******************************************************************************
** DeletePointCommand
*/

DeletePointCommand::DeletePointCommand(qint32 routeIndex, qint32 pointIndex, MapViewProxy *proxy,
                                       QTableWidget *routeWidget, QTableWidget *pointWidget,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_proxy = proxy;
    m_routeWidget = routeWidget;
    m_pointWidget = pointWidget;
}

void DeletePointCommand::undo()
{
    m_pointWidget->insertRow(m_pointIndex);
    m_pointWidget->setItem(m_pointIndex, 0, new QTableWidgetItem(QString::number(m_point.latitude())));
    m_pointWidget->setItem(m_pointIndex, 1, new QTableWidgetItem(QString::number(m_point.longitude())));
    Route &route = RouteStore::instance()->getRoute(m_routeIndex);
    route.insertCoordinate(m_pointIndex, m_point);
    route.updateLength();
    m_routeWidget->item(m_routeIndex, 1)->setText(QString::number(route.getLength() / 1000));
    emit m_proxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}

void DeletePointCommand::redo()
{
    m_pointWidget->removeRow(m_pointIndex);
    Route &route = RouteStore::instance()->getRoute(m_routeIndex);
    m_point = route.getCoordinates().coordinateAt(m_pointIndex);
    route.removeCoordinate(m_pointIndex);
    route.updateLength();
    m_routeWidget->item(m_routeIndex, 1)->setText(QString::number(route.getLength() / 1000));
    emit m_proxy->setPolyline(QVariant::fromValue(route.getCoordinates()));
}
