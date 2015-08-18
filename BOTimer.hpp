#ifndef BO_TIMER_HPP
#define BO_TIMER_HPP

#include <QObject>

class BOTimer : public QObject
{
    Q_OBJECT

  public:
    explicit BOTimer(QObject* parent = nullptr);
    ~BOTimer();

  private:
    Q_DISABLE_COPY(BOTimer);
};

#endif // BO_TIMER_HPP
