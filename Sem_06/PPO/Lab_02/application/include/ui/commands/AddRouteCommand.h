//
// Created by lieroz on 13.05.18.
//

#include <QUndoCommand>
#include <functional>

#include <data/models/Route.h>

class AddRouteCommand : public QUndoCommand
{
public:
    AddRouteCommand(QSharedPointer<Route> route,
                    const std::function<void(QSharedPointer<Route>)> &redoFunc,
                    const std::function<void()> &undoFunc,
                    QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;

private:
    QSharedPointer<Route> m_route;
    std::function<void(QSharedPointer<Route>)> m_redoFunc;
    std::function<void()> m_undoFunc;
};
