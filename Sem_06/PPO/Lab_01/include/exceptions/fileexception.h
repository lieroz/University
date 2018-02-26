#pragma once

#include <exceptions/abstractexception.h>

class FileException : public AbstractException
{
public:
    FileException(QString message) : AbstractException(message)
    {
    }

    virtual ~FileException()
    {
    }

    void raise() const
    {
        throw *this;
    }

    FileException *clone() const
    {
        return new FileException(*this);
    }
};
