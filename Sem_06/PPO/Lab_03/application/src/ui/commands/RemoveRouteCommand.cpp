//
// Created by lieroz on 13.05.18.
//

#include <ui/commands/RemoveRouteCommand.h>

RemoveRouteCommand::RemoveRouteCommand(QSharedPointer<Route> route,
                                       const std::function<void()> &redoFunc,
                                       const std::function<void(QSharedPointer<Route>)> &undoFunc,
                                       QUndoCommand *parent)
    : m_route(route), m_redoFunc(redoFunc), m_undoFunc(undoFunc), QUndoCommand(parent)
{
}

void RemoveRouteCommand::undo()
{
    m_undoFunc(m_route);
}

void RemoveRouteCommand::redo()
{
    m_redoFunc();
}
