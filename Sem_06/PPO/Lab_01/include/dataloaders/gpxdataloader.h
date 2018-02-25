#pragma once

#include <dataloaders/xmldataloader.h>

class GPXDataLoader : public XMLDataLoader
{
public:
    GPXDataLoader(QObject *parent = Q_NULLPTR);
    virtual~GPXDataLoader();

    virtual void load() override;
    virtual void save() override;
};
