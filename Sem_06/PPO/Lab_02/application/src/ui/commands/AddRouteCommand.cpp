//
// Created by lieroz on 13.05.18.
//

#include <ui/commands/AddRouteCommand.h>

AddRouteCommand::AddRouteCommand(QSharedPointer<Route> route,
                                 const std::function<void (QSharedPointer<Route>)> &redoFunc,
                                 const std::function<void ()> &undoFunc,
                                 QUndoCommand *parent)
    : m_route(route), m_redoFunc(redoFunc), m_undoFunc(undoFunc), QUndoCommand(parent)
{
}

void AddRouteCommand::undo()
{
    m_undoFunc();
}

void AddRouteCommand::redo()
{
    m_redoFunc(m_route);
}
