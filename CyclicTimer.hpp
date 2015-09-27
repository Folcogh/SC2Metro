#ifndef CYCLIC_TIMER_HPP
#define CYCLIC_TIMER_HPP

#include "Game.hpp"
#include "CyclicTimerData.hpp"

class Game;
class CyclicTimer
{
  public:
    CyclicTimer(Game* game, CyclicTimerData* data);
    ~CyclicTimer();
    const CyclicTimerData* data();

  private:
    Q_DISABLE_COPY(CyclicTimer)
    Game* Parent;
    const CyclicTimerData* Data;
};

#endif // CYCLIC_TIMER_HPP
