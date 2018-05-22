//
// Created by lieroz on 13.05.18.
//

#include <QUndoCommand>
#include <functional>

#include <data/models/Route.h>

class RemoveRouteCommand : public QUndoCommand
{
public:
    RemoveRouteCommand(QSharedPointer<Route> route,
                       const std::function<void()> &redoFunc,
                       const std::function<void(QSharedPointer<Route>)> &undoFunc,
                       QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QSharedPointer<Route> m_route;
    std::function<void()> m_redoFunc;
    std::function<void(QSharedPointer<Route>)> m_undoFunc;
};
