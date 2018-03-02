#pragma once

#include <QtWidgets/QUndoCommand>
#include <QTableWidget>

#include <common/routestore.h>
#include <mainwindow.h>

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
                    QTableWidget *widget, QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    QTableWidget *m_widget;
};

class ModifyPointCommand : public QUndoCommand
{
public:
    ModifyPointCommand(qint32 routeIndex, qint32 pointIndex, MapViewProxy *proxy,
                       QTableWidget *routeWidget, QTableWidget *pointWidget,
                       const QGeoCoordinate &point, const QGeoCoordinate &oldPoint,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    MapViewProxy *m_proxy;
    QTableWidget *m_routeWidget;
    QTableWidget *m_pointWidget;
    QGeoCoordinate m_point;
    QGeoCoordinate m_oldPoint;
};

class DeletePointCommand : public QUndoCommand
{
public:
    DeletePointCommand(qint32 routeIndex, qint32 pointIndex, MapViewProxy *proxy,
                       QTableWidget *routeWidget, QTableWidget *pointWidget,
                       QUndoCommand *parent = Q_NULLPTR);

    void undo() override;
    void redo() override;

private:
    qint32 m_routeIndex;
    qint32 m_pointIndex;
    MapViewProxy *m_proxy;
    QTableWidget *m_routeWidget;
    QTableWidget *m_pointWidget;
    QGeoCoordinate m_point;
};
