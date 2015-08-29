#ifndef CYCLIC_TIMER_HPP
#define CYCLIC_TIMER_HPP

#include "CyclicTimerData.hpp"

class CyclicTimer
{
  public:
    explicit CyclicTimer(CyclicTimerData* data);
    ~CyclicTimer();

  private:
    Q_DISABLE_COPY(CyclicTimer)
    CyclicTimerData* Data;
};

#endif // CYCLIC_TIMER_HPP
