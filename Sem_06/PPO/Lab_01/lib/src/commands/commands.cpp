#include <commands/commands.h>
#include <QDebug>

AddRouteCommand::AddRouteCommand(qint32 index, const Route &route,
                                 QTableWidget *widget, QUndoCommand *parent)
    : m_route(route), QUndoCommand(parent)
{
    m_index = index;
    m_widget = widget;
}

void AddRouteCommand::undo()
{
    m_widget->removeRow(m_index);
    RouteStore::instance()->deleteRoute(m_index);
}

void AddRouteCommand::redo()
{
    m_widget->insertRow(m_index);
    m_widget->setItem(m_index, 0, new QTableWidgetItem(m_route.getName()));

    QTableWidgetItem *item;
    item = new QTableWidgetItem(QString::number(m_route.getLength() / 1000));
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    m_widget->setItem(m_index, 1, item);

    item = new QTableWidgetItem(m_route.getDate().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    m_widget->setItem(m_index, 2, item);
    RouteStore::instance()->addRoute(m_route);
}

/******************************************************************************
** DeleteRouteCommand
*/

DeleteRouteCommand::DeleteRouteCommand(qint32 index, QTableWidget *widget, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_index = index;
    m_widget = widget;
}

void DeleteRouteCommand::undo()
{
    m_widget->insertRow(m_index);
    m_widget->setItem(m_index, 0, new QTableWidgetItem(m_route.getName()));

    QTableWidgetItem *item;
    item = new QTableWidgetItem(QString::number(m_route.getLength() / 1000));
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    m_widget->setItem(m_index, 1, item);

    item = new QTableWidgetItem(m_route.getDate().toString());
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    m_widget->setItem(m_index, 2, item);
    RouteStore::instance()->addRoute(m_route);
}

void DeleteRouteCommand::redo()
{
    m_route = RouteStore::instance()->getRoute(m_index);
    m_widget->removeRow(m_index);
    RouteStore::instance()->deleteRoute(m_index);
}

/******************************************************************************
** AddPointCommand
*/

AddPointCommand::AddPointCommand(qint32 routeIndex, qint32 pointIndex,
                                 const QGeoCoordinate &point, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_point = point;
}

void AddPointCommand::undo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).removeCoordinate(m_pointIndex);
}

void AddPointCommand::redo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).insertCoordinate(m_pointIndex, m_point);
}

/******************************************************************************
** ModifyPointCommand
*/

ModifyPointCommand::ModifyPointCommand(qint32 routeIndex, qint32 pointIndex,
                                       const QGeoCoordinate &oldPoint, const QGeoCoordinate &newPoint,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_oldPoint = oldPoint;
    m_newPoint = newPoint;
}

void ModifyPointCommand::undo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).replaceCoordinate(m_pointIndex, m_oldPoint);
}

void ModifyPointCommand::redo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).replaceCoordinate(m_pointIndex, m_newPoint);
}

/******************************************************************************
** DeletePointCommand
*/

DeletePointCommand::DeletePointCommand(qint32 routeIndex, qint32 pointIndex,
                                       const QGeoCoordinate &point, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_point = point;
}

void DeletePointCommand::undo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).insertCoordinate(m_pointIndex, m_point);
}

void DeletePointCommand::redo()
{
//    RouteStore::instance()->getRoute(m_routeIndex).removeCoordinate(m_pointIndex);
}
