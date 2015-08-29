#include "CyclicTimerSpec.hpp"

CyclicTimerSpec::CyclicTimerSpec()
{
}

int CyclicTimerSpec::periodMin() const
{
    return PeriodMin;
}

int CyclicTimerSpec::periodMax() const
{
    return PeriodMax;
}

int CyclicTimerSpec::defaultPeriod() const
{
    return DefaultPeriod;
}

int CyclicTimerSpec::periodStep() const
{
    return PeriodStep;
}

int CyclicTimerSpec::periodPageStep() const
{
    return PeriodPageStep;
}

int CyclicTimerSpec::boundMin() const
{
    return BoundMin;
}

int CyclicTimerSpec::boundMax() const
{
    return BoundMax;
}

int CyclicTimerSpec::defaultStart() const
{
    return DefaultStart;
}

int CyclicTimerSpec::defaultTerminate() const
{
    return DefaultTerminate;
}

int CyclicTimerSpec::boundStep() const
{
    return BoundStep;
}

int CyclicTimerSpec::boundPageStep() const
{
    return BoundPageStep;
}

int CyclicTimerSpec::volumeMin() const
{
    return VolumeMin;
}

int CyclicTimerSpec::volumeMax() const
{
    return VolumeMax;
}

int CyclicTimerSpec::defaultVolume() const
{
    return DefaultVolume;
}

int CyclicTimerSpec::volumeStep() const
{
    return VolumeStep;
}

int CyclicTimerSpec::volumePageStep() const
{
    return VolumePageStep;
}
