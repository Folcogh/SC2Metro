#include "FException.hpp"

FException::FException(QString msg)
{
    Message = msg;
}

FException::~FException()
{
}

QString FException::message() const
{
    return Message;
}
