//
// Created by lieroz on 13.05.18.
//

#include <QUndoCommand>
#include <functional>

#include <data/models/Coordinate.h>

class RemoveCoordinateCommand : public QUndoCommand
{
public:
    RemoveCoordinateCommand(const Coordinate &coordinate,
                            const std::function<void ()> &redoFunc,
                            const std::function<void (const Coordinate &)> &undoFunc,
                            QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    Coordinate m_coordinate;
    std::function<void ()> m_redoFunc;
    std::function<void (const Coordinate &)> m_undoFunc;
};
