//
// Created by lieroz on 13.05.18.
//

#include <ui/commands/RemoveCoordinateCommand.h>

RemoveCoordinateCommand::RemoveCoordinateCommand(const Coordinate &coordinate,
        const std::function<void ()> &redoFunc,
        const std::function<void (const Coordinate &)> &undoFunc,
        QUndoCommand *parent)
    : m_coordinate(coordinate), m_redoFunc(redoFunc), m_undoFunc(undoFunc), QUndoCommand(parent)
{
}

void RemoveCoordinateCommand::undo()
{
    m_undoFunc(m_coordinate);
}

void RemoveCoordinateCommand::redo()
{
    m_redoFunc();
}
