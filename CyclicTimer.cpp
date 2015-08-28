#include "CyclicTimer.hpp"

CyclicTimer::CyclicTimer(CyclicTimerData* data)
{
    Period = data->period();
    Start = data->start();
    Terminate = data->terminate();
    Volume = data->volume();
    Sound = data->sound();
    Hotkey = data->hotkey();
}

CyclicTimer::~CyclicTimer()
{
}
