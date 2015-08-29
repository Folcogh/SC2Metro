#include "CyclicTimer.hpp"

CyclicTimer::CyclicTimer(CyclicTimerData* data)
{
    Data = data;
}

CyclicTimer::~CyclicTimer()
{
    delete Data;
}
