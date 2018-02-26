#pragma once

#include <dataloaders/abstractdataloader.h>

class XMLDataLoader : public AbstractDataLoader
{
public:
    XMLDataLoader(QString fileName, QString field, QObject *parent = Q_NULLPTR);
    virtual ~XMLDataLoader();

    virtual void load() override;
    virtual void save() override;

protected:
    QString m_field;
};
