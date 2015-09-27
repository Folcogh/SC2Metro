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

bool CyclicTimerData::enabled() const
{
    return Enabled;
}

int CyclicTimerData::period() const
{
    return Period;
}

int CyclicTimerData::start() const
{
    return Start;
}

int CyclicTimerData::terminate() const
{
    return Terminate;
}

int CyclicTimerData::volume() const
{
    return Volume;
}

QString CyclicTimerData::sound() const
{
    return Sound;
}

QKeySequence CyclicTimerData::hotkey() const
{
    return Hotkey;
}

void CyclicTimerData::setEnabled(bool enabled)
{
    Enabled = enabled;
}
