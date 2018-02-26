#pragma once

#include <dataloaders/xmldataloader.h>

class GPXDataLoader : public XMLDataLoader
{
public:
    GPXDataLoader(QString fileName, QObject *parent = Q_NULLPTR);
    virtual~GPXDataLoader();

    virtual void load() override;
    virtual void save() override;
};
