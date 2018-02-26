#pragma once

#include <dataloaders/abstractdataloader.h>

class XMLDataLoader : public AbstractDataLoader
{
public:
    XMLDataLoader(QString fileName, QObject *parent = Q_NULLPTR);
    virtual ~XMLDataLoader();

    virtual void load() override;
    virtual void save() override;
};
