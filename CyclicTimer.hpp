#ifndef CYCLIC_TIMER_HPP
#define CYCLIC_TIMER_HPP

#include <QObject>

class CyclicTimer : public QObject
{
    Q_OBJECT

  public:
    explicit CyclicTimer(QObject* parent = nullptr);
    ~CyclicTimer();

  private:
    Q_DISABLE_COPY(CyclicTimer)
};

#endif // CYCLIC_TIMER_HPP
