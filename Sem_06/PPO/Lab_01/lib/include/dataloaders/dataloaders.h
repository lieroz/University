#pragma once

#include <QObject>

class AbstractDataLoader : public QObject
{
public:
    AbstractDataLoader(const QString &fileName, QObject *parent = Q_NULLPTR);
    virtual ~AbstractDataLoader();

    virtual void load() = 0;

protected:
    QString m_fileName;
};

class GpxDataLoader : public AbstractDataLoader
{
public:
    GpxDataLoader(const QString &fileName, QObject *parent = Q_NULLPTR);
    virtual~GpxDataLoader();

    virtual void load() override;
};
