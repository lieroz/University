//
// Created by lieroz on 13.05.18.
//

#include <ui/commands/UpdateCoordinateCommand.h>

UpdateCoordinateCommand::UpdateCoordinateCommand(const Coordinate &oldCoordinate,
        const Coordinate &newCoordinate,
        const std::function<void (const Coordinate &)> &undoRedoFunc,
        QUndoCommand *parent)
    : m_oldCoordinate(oldCoordinate), m_newCoordinate(newCoordinate),
      m_undoRedoFunc(undoRedoFunc), QUndoCommand(parent)
{
}

void UpdateCoordinateCommand::undo()
{
    m_undoRedoFunc(m_oldCoordinate);
}

void UpdateCoordinateCommand::redo()
{
    m_undoRedoFunc(m_newCoordinate);
}
