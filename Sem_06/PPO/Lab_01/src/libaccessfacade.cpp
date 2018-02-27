#include <libaccessfacade.h>
#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

#include <QFileInfo>

LibAccessFacade::LibAccessFacade(QObject *parent) : QObject(parent)
{
    m_store.reset(RouteStore::instance());
}

LibAccessFacade::~LibAccessFacade()
{

}

void LibAccessFacade::load(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    if (!fileInfo.exists() || !fileInfo.isFile()) {
        throw FileException("file doesn't exist");
    }

    auto createFunc = LoaderFactory::createDataloader(fileInfo.completeSuffix());
    m_loader.reset(createFunc(fileName));
    m_loader->load();
}
