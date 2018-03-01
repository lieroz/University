#pragma once

#include <QtWidgets/QUndoCommand>
#include <QTableWidget>

#include <common/routestore.h>

class AddRouteCommand : public QUndoCommand
{
public:
    AddRouteCommand(qint32 index, const Route &route,
                    QTableWidget *widget, QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_index;
    Route m_route;
    QTableWidget *m_widget;
};

class DeleteRouteCommand : public QUndoCommand
{
public:
    DeleteRouteCommand(qint32 index, QTableWidget *widget, QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_index;
    Route m_route;
    QTableWidget *m_widget;
};

class AddPointCommand : public QUndoCommand
{
public:
    AddPointCommand(qint32 routeIndex, qint32 pointIndex,
                    const QGeoCoordinate &point, QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    QGeoCoordinate m_point;
};

class ModifyPointCommand : public QUndoCommand
{
public:
    ModifyPointCommand(qint32 routeIndex, qint32 pointIndex,
                       const QGeoCoordinate &oldPoint, const QGeoCoordinate &newPoint,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    QGeoCoordinate m_newPoint;
    QGeoCoordinate m_oldPoint;
};

class DeletePointCommand : public QUndoCommand
{
public:
    DeletePointCommand(qint32 routeIndex, qint32 pointIndex,
                       const QGeoCoordinate &point, QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    QGeoCoordinate m_point;
};
