//
// Created by lieroz on 10.05.18.
//

#include <data/models/Route.h>

Route::Route()
    : m_length(0), m_created(QDateTime::currentDateTime())
{
}

Route::Route(const Route &other)
    : m_name(other.m_name), m_length(other.m_length), m_created(other.m_created), m_path(other.m_path)
{
}

Route::Route(Route &&other)
    : m_name(other.m_name), m_length(other.m_length), m_created(other.m_created), m_path(other.m_path)
{
    other.m_name.clear();
    other.m_length = 0;
    other.m_created = QDateTime::currentDateTime(); // TODO maybe set to zero
    other.m_path.clear();
}

Route::Route(const QString &name, const QVector<Coordinate> &path)
    : m_name(name), m_length(0), m_created(QDateTime::currentDateTime()), m_path(path)
{
    updateLength();
}

Route &Route::operator=(const Route &other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_length = other.m_length;
        m_created = other.m_created;
        m_path = other.m_path;
    }
    return *this;
}

Route &Route::operator=(Route &&other) noexcept
{
    if (this != &other) {
        m_name = other.m_name;
        m_length = other.m_length;
        m_created = other.m_created;
        m_path = other.m_path;

        other.m_name.clear();
        other.m_length = 0;
        other.m_created = QDateTime::currentDateTime(); // TODO maybe set to zero
        other.m_path.clear();
    }
    return *this;
}

const QString &Route::getName()
{
    return m_name;
}

double Route::getLength()
{
    return m_length;
}

const QDateTime &Route::getCreated()
{
    return m_created;
}

const QVector<Coordinate> &Route::getPath()
{
    return m_path;
}

void Route::setName(const QString &name)
{
    m_name = name;
}

void Route::setPath(const QVector<Coordinate> &path)
{
    m_path = path;
}

bool Route::addCoordinate(qint32 index, const Coordinate &coordinate)
{
    if (index < 0 || index > m_path.size()) {
        return false;
    }
    m_path.insert(index, coordinate);
    updateLength();
    return true;
}

void Route::addCoordinate(const Coordinate &coordinate)
{
    m_path.push_back(coordinate);
    updateLength();
}

bool Route::removeCoordinate(qint32 index)
{
    if (index < 0 || index >= m_path.size()) {
        return false;
    }
    m_path.erase(std::begin(m_path) + index);
    updateLength();
    return true;
}

void Route::removeCoordinate()
{
    m_path.pop_back();
    updateLength();
}

bool Route::updateCoordinate(qint32 index, const Coordinate &coordinate)
{
    if (index < 0 || index >= m_path.size()) {
        return false;
    }
    m_path[index] = coordinate;
    updateLength();
    return true;
}

QSharedPointer<Coordinate> Route::getCoordinate(qint32 index)
{
    if (index < 0 || index >= m_path.size()) {
        return nullptr;
    }
    return QSharedPointer<Coordinate>::create(m_path[index]);
}

void Route::updateLength()
{
    m_length = 0;
    for (auto i = 0; i < m_path.size() - 1; ++i) {
        m_length += m_path[i].distanceTo(m_path[i + 1]);
    }
}
