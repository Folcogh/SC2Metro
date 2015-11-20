#include "CyclicTimer.hpp"

CyclicTimer::CyclicTimer()
{
    m_period = 0;
    m_start = 0;    // Start immediately
    m_terminate = 0; // Never terminate
    m_volume = 100; // Volume max
    m_hotkey = QKeySequence();
}

void CyclicTimer::setSound(QString sound)
{
    m_sound = sound;
}

void CyclicTimer::setPeriod(int period)
{
    m_period = period;
}

void CyclicTimer::setStart(int start)
{
    m_start = start;
}

void CyclicTimer::setTerminate(int terminate)
{
    m_terminate = terminate;
}

void CyclicTimer::setVolume(int volume)
{
    m_volume = volume;
}

void CyclicTimer::setHotkey(QKeySequence hotkey)
{
    m_hotkey = hotkey;
}

QString CyclicTimer::getSound()
{
    return m_sound;
}

int CyclicTimer::getPeriod()
{
    return m_period;
}

int CyclicTimer::getStart()
{
    return m_start;
}

int CyclicTimer::getTerminate()
{
    return m_terminate;
}

int CyclicTimer::getVolume()
{
    return m_volume;
}

QKeySequence CyclicTimer::getHotkey()
{
    return m_hotkey;
}

