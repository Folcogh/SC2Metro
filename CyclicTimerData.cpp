#include "CyclicTimerData.hpp"

CyclicTimerData::CyclicTimerData(int period, int start, int terminate, int volume, QString sound, QKeySequence hotkey)
    : Period(period)
    , Start(start)
    , Terminate(terminate)
    , Volume(volume)
    , Sound(sound)
    , Hotkey(hotkey)
{
    Enabled = true;
}

bool CyclicTimerData::enabled()
{
    return Enabled;
}

int CyclicTimerData::period()
{
    return Period;
}

int CyclicTimerData::start()
{
    return Start;
}

int CyclicTimerData::terminate()
{
    return Terminate;
}

int CyclicTimerData::volume()
{
    return Volume;
}

QString CyclicTimerData::sound()
{
    return Sound;
}

QKeySequence CyclicTimerData::hotkey()
{
    return Hotkey;
}
