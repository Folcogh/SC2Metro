#include "CyclicTimer.hpp"

CyclicTimer::CyclicTimer(Game* game, CyclicTimerData* data)
{
    Parent = game;
    Data = data;
}

CyclicTimer::~CyclicTimer()
{
    delete Data;
}

const CyclicTimerData* CyclicTimer::data()
{
    return Data;
}
