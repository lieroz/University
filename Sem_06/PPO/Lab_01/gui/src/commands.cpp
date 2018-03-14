#include <commands.h>

AddRouteCommand::AddRouteCommand(QSharedPointer<Route> route,
                                 const std::function<void (QSharedPointer<Route>)> &redoFunc,
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

DeleteRouteCommand::DeleteRouteCommand(QSharedPointer<Route> route,
                                       const std::function<void ()> &redoFunc,
                                       const std::function<void (QSharedPointer<Route>)> &undoFunc,
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

AddPointCommand::AddPointCommand(const QGeoCoordinate &point,
                                 const std::function<void (QGeoCoordinate &)> &redoFunc,
                                 const std::function<void ()> &undoFunc,
                                 QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_point = point;
    m_redoFunc = redoFunc;
    m_undoFunc = undoFunc;
}

void AddPointCommand::undo()
{
    m_undoFunc();
}

void AddPointCommand::redo()
{
    m_redoFunc(m_point);
}

/******************************************************************************
** ModifyPointCommand
*/

ModifyPointCommand::ModifyPointCommand(const QGeoCoordinate &point,
                                       const QGeoCoordinate &oldPoint,
                                       const std::function<void (QGeoCoordinate &)> &undoRedoFunc,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_point = point;
    m_oldPoint = oldPoint;
    m_undoRedoFunc = undoRedoFunc;
}

void ModifyPointCommand::undo()
{
    m_undoRedoFunc(m_oldPoint);
}

void ModifyPointCommand::redo()
{
    m_undoRedoFunc(m_point);
}

/******************************************************************************
** DeletePointCommand
*/

DeletePointCommand::DeletePointCommand(const QGeoCoordinate &point,
                                       const std::function<void ()> &redoFunc,
                                       const std::function<void (QGeoCoordinate &)> &undoFunc,
                                       QUndoCommand *parent)
    : QUndoCommand(parent)
{
    m_point = point;
    m_redoFunc = redoFunc;
    m_undoFunc = undoFunc;
}

void DeletePointCommand::undo()
{
    m_undoFunc(m_point);
}

void DeletePointCommand::redo()
{
    m_redoFunc();
}
