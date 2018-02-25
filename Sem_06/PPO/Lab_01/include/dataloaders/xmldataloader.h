#pragma once

#include <dataloaders/dataloader.h>

class XMLDataLoader : public DataLoader
{
public:
    XMLDataLoader(QObject *parent = Q_NULLPTR);
    virtual ~XMLDataLoader();

    virtual void load() override;
    virtual void save() override;
};
