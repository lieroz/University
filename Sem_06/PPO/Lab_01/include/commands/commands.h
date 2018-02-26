#pragma once

#include <QtWidgets/QUndoCommand>

class CreateRouteCommand : public QUndoCommand
{
public:
    CreateRouteCommand(QObject *parent = Q_NULLPTR);
};

class LoadRouteCommand : public QUndoCommand
{

};

class DeleteRouteCommand : public QUndoCommand
{

};

class CreateRoutePointCommand : public QUndoCommand
{

};

class ModifyRoutePointCommand : public QUndoCommand
{

};

class DeleteRoutePointCommand : public QUndoCommand
{

};
