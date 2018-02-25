#pragma once

#include <QObject>

class DataLoader : public QObject
{
public:
    DataLoader(QObject *parent = Q_NULLPTR) : QObject(parent)
    {
    }

    virtual ~DataLoader()
    {
    }

    virtual void load() = 0;
    virtual void save() = 0;
};
