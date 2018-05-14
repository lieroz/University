//
// Created by lieroz on 13.05.18.
//

#include <ui/commands/AddCoordinateCommand.h>

AddCoordinateCommand::AddCoordinateCommand(const Coordinate &coordinate,
        const std::function<void (const Coordinate &)> &redoFunc,
        const std::function<void ()> &undoFunc,
        QUndoCommand *parent)
    : m_coordinate(coordinate), m_redoFunc(redoFunc), m_undoFunc(undoFunc), QUndoCommand(parent)
{
}

void AddCoordinateCommand::undo()
{
    m_undoFunc();
}

void AddCoordinateCommand::redo()
{
    m_redoFunc(m_coordinate);
}
