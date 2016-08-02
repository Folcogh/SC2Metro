#include "SMException.hpp"

SMException::SMException(QString message)
    : message(message)
{
}

QString SMException::getMessage() const
{
    return this->message;
}
