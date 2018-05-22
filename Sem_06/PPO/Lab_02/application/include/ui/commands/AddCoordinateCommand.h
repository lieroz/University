//
// Created by lieroz on 13.05.18.
//

#include <QUndoCommand>
#include <functional>

#include <data/models/Coordinate.h>

class AddCoordinateCommand : public QUndoCommand
{
public:
    AddCoordinateCommand(const Coordinate &coordinate,
                         const std::function<void (const Coordinate &)> &redoFunc,
                         const std::function<void ()> &undoFunc,
                         QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    Coordinate m_coordinate;
    std::function<void (const Coordinate &)> m_redoFunc;
    std::function<void ()> m_undoFunc;
};
