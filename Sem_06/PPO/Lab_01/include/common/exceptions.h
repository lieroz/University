#pragma once

#include <QException>

class AbstractException : public QException
{
public:
    AbstractException(QString message)
        : QException(), m_message(message)
    {
    }

    virtual ~AbstractException()
    {
    }

    virtual void raise() const = 0;
    virtual AbstractException *clone() const = 0;

    QString message() const
    {
        return m_message;
    }

protected:
    QString m_message;
};

class FileException : public AbstractException
{
public:
    FileException(QString message) : AbstractException(message)
    {
    }

    virtual ~FileException()
    {
    }

    virtual void raise() const
    {
        throw *this;
    }

    virtual FileException *clone() const
    {
        return new FileException(*this);
    }
};

class ExtensionException : public AbstractException
{
public:
    ExtensionException(QString message) : AbstractException(message)
    {
    }

    virtual ~ExtensionException()
    {
    }

    virtual void raise() const
    {
        throw *this;
    }

    virtual ExtensionException *clone() const
    {
        return new ExtensionException(*this);
    }
};
