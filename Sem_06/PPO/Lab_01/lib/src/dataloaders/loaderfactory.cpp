#include <dataloaders/loaderfactory.h>
#include <common/exceptions.h>

QMap<QString, std::function<AbstractDataLoader *(const QString &)>> registeredFileTypes = {
    std::make_pair("gpx", [](const QString & fileName)
    {
        return new GpxDataLoader(fileName);
    })
};

std::function<AbstractDataLoader *(const QString &)> LoaderFactory::createDataloader(
    const QString &fileType)
{
    Q_FOREACH (QString key, registeredFileTypes.keys()) {
        if (key == fileType) {
            return registeredFileTypes[key];
        }
    }

    throw ExtensionException("invalid file format");
}
