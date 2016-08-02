#ifndef SMEXCEPTION_HPP
#define SMEXCEPTION_HPP

#include <QString>

class SMException
{
  public:
    explicit SMException(QString message);
    QString getMessage() const;

  private:
    QString message;
};

#endif // SMEXCEPTION_HPP
