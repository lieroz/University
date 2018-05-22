//
// Created by lieroz on 22.05.18.
//

#include <QDebug>

#include <TurnsPlugin.h>

QString TurnsPlugin::echo(const QString &message)
{
    qDebug() << message;
    return message;
}
