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
    Q_DISABLE_COPY(FException)
    QString Message;
};

#endif // FEXCEPTION_HPP
