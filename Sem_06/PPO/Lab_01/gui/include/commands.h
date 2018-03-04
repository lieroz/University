#pragma once

#include <QtWidgets/QUndoCommand>
#include <functional>

#include <common/routestore.h>
#include <mainwindow.h>

class AddRouteCommand : public QUndoCommand
{
public:
    AddRouteCommand(const Route &route,
                    const std::function<void (Route &)> &redoFunc,
                    const std::function<void ()> &undoFunc,
                    QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    Route m_route;
    std::function<void (Route &)> m_redoFunc;
    std::function<void ()> m_undoFunc;
};

class DeleteRouteCommand : public QUndoCommand
{
public:
    DeleteRouteCommand(const Route &route,
                       const std::function<void ()> &redoFunc,
                       const std::function<void (Route &)> &undoFunc,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    Route m_route;
    std::function<void ()> m_redoFunc;
    std::function<void (Route &)> m_undoFunc;
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
