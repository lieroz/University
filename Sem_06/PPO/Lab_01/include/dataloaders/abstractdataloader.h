#pragma once

#include <QObject>

class AbstractDataLoader : public QObject
{
public:
    AbstractDataLoader(QString fileName, QObject *parent = Q_NULLPTR)
        : m_fileName(fileName), QObject(parent)
    {
    }

    virtual ~AbstractDataLoader()
    {
    }

    virtual void load() = 0;
    virtual void save() = 0;

protected:
    QString m_fileName;
};
