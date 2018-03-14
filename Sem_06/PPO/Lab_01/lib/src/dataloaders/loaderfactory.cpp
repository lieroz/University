#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

QMap<QString, LoaderFunc> registeredFileTypes = {
    std::make_pair("gpx", GpxDataLoader::load)
};

LoaderFunc LoaderFactory::getDataloader(const QString &fileType)
{
    Q_FOREACH (QString key, registeredFileTypes.keys()) {
        if (key == fileType) {
            return registeredFileTypes[key];
        }
    }

    throw ExtensionException("invalid file format");
}
