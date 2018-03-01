#pragma once

#include <common/route.h>

class AbstractDataLoader
{
    Q_DISABLE_COPY(AbstractDataLoader)

public:
    AbstractDataLoader(const QString &fileName);
    virtual ~AbstractDataLoader() = default;

    virtual void load(Route &route) = 0;
    void reset(const QString& fileName);

protected:
    QString m_fileName;
};

class GpxDataLoader : public AbstractDataLoader
{
    Q_DISABLE_COPY(GpxDataLoader)

public:
    GpxDataLoader(const QString &fileName);
    ~GpxDataLoader() = default;

    void load(Route &route) override;
};
