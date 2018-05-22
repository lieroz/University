//
// Created by lieroz on 13.05.18.
//

#include <QUndoCommand>
#include <functional>

#include <data/models/Coordinate.h>

class UpdateCoordinateCommand : public QUndoCommand
{
public:
    UpdateCoordinateCommand(const Coordinate &oldCoordinate,
                            const Coordinate &newCoordinate,
                            const std::function<void (const Coordinate &)> &undoRedoFunc,
                            QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    Coordinate m_oldCoordinate;
    Coordinate m_newCoordinate;
    std::function<void (const Coordinate &)> m_undoRedoFunc;
};
