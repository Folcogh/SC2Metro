#ifndef FEXCEPTION_HPP
#define FEXCEPTION_HPP

#include <QString>

class FException
{
public:
    explicit FException(QString msg);
    virtual ~FException();
    QString message() const;

private:
    QString Message;
};

#endif // FEXCEPTION_HPP
