#pragma once

#include <QtWidgets/QUndoCommand>
#include <QSharedPointer>
#include <functional>

#include <common/route.h>

class AddRouteCommand : public QUndoCommand
{
public:
    AddRouteCommand(QSharedPointer<Route> route,
                    const std::function<void (QSharedPointer<Route>)> &redoFunc,
                    const std::function<void ()> &undoFunc,
                    QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    QSharedPointer<Route> m_route;
    std::function<void (QSharedPointer<Route>)> m_redoFunc;
    std::function<void ()> m_undoFunc;
};

class DeleteRouteCommand : public QUndoCommand
{
public:
    DeleteRouteCommand(QSharedPointer<Route> route,
                       const std::function<void ()> &redoFunc,
                       const std::function<void (QSharedPointer<Route>)> &undoFunc,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    QSharedPointer<Route> m_route;
    std::function<void ()> m_redoFunc;
    std::function<void (QSharedPointer<Route>)> m_undoFunc;
};

class AddPointCommand : public QUndoCommand
{
public:
    AddPointCommand(const QGeoCoordinate &point,
                    const std::function<void (QGeoCoordinate &)> &redoFunc,
                    const std::function<void ()> &undoFunc,
                    QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    QGeoCoordinate m_point;
    std::function<void (QGeoCoordinate &)> m_redoFunc;
    std::function<void ()> m_undoFunc;
};

class ModifyPointCommand : public QUndoCommand
{
public:
    ModifyPointCommand(const QGeoCoordinate &point,
                       const QGeoCoordinate &oldPoint,
                       const std::function<void (QGeoCoordinate &)> &undoRedoFunc,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    QGeoCoordinate m_point;
    QGeoCoordinate m_oldPoint;
    std::function<void (QGeoCoordinate &)> m_undoRedoFunc;
};

class DeletePointCommand : public QUndoCommand
{
public:
    DeletePointCommand(const QGeoCoordinate &point,
                       const std::function<void ()> &redoFunc,
                       const std::function<void (QGeoCoordinate &)> &undoFunc,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    QGeoCoordinate m_point;
    std::function<void ()> m_redoFunc;
    std::function<void (QGeoCoordinate &)> m_undoFunc;
};
