#ifndef SMEXCEPTION_HPP
#define SMEXCEPTION_HPP

#include <QString>

class SMException
{
  public:
    explicit SMException(QString message) : message(message) {}
    QString getMessage() const { return message; }

  private:
    QString message;
};

#endif // SMEXCEPTION_HPP
