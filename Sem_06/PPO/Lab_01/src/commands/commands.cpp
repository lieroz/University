#include <commands/commands.h>

AddRouteCommand::AddRouteCommand(qint32 index, const Route &route, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_index = index;
    m_route = route;
}

void AddRouteCommand::undo()
{
    RouteStore::instance()->deleteRoute(m_index);
}

void AddRouteCommand::redo()
{
    RouteStore::instance()->addRoute(m_route);
}

/******************************************************************************
** DeleteRouteCommand
*/

DeleteRouteCommand::DeleteRouteCommand(qint32 index, const Route &route, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_index = index;
    m_route = route;
}

void DeleteRouteCommand::undo()
{
    RouteStore::instance()->insertRoute(m_index, m_route);
}

void DeleteRouteCommand::redo()
{
    RouteStore::instance()->deleteRoute(m_index);
}

/******************************************************************************
** AddPointCommand
*/

AddPointCommand::AddPointCommand(qint32 routeIndex, qint32 pointIndex,
                                 const QPointF &point, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_point = point;
}

void AddPointCommand::undo()
{
    RouteStore::instance()->getRoute(m_routeIndex).removeCoordinate(m_pointIndex);
}

void AddPointCommand::redo()
{
    RouteStore::instance()->getRoute(m_routeIndex).insertCoordinate(m_pointIndex, m_point);
}

/******************************************************************************
** ModifyPointCommand
*/

ModifyPointCommand::ModifyPointCommand(qint32 routeIndex, qint32 pointIndex,
                                       const QPointF &oldPoint, const QPointF &newPoint,
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
    RouteStore::instance()->getRoute(m_routeIndex).replaceCoordinate(m_pointIndex, m_oldPoint);
}

void ModifyPointCommand::redo()
{
    RouteStore::instance()->getRoute(m_routeIndex).replaceCoordinate(m_pointIndex, m_newPoint);
}

/******************************************************************************
** DeletePointCommand
*/

DeletePointCommand::DeletePointCommand(qint32 routeIndex, qint32 pointIndex,
                                       const QPointF &point, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_routeIndex = routeIndex;
    m_pointIndex = pointIndex;
    m_point = point;
}

void DeletePointCommand::undo()
{
    RouteStore::instance()->getRoute(m_routeIndex).insertCoordinate(m_pointIndex, m_point);
}

void DeletePointCommand::redo()
{
    RouteStore::instance()->getRoute(m_routeIndex).removeCoordinate(m_pointIndex);
}
