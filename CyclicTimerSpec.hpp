#ifndef CYCLIC_TIMER_SPEC_HPP
#define CYCLIC_TIMER_SPEC_HPP

#include <QtGlobal>

class CyclicTimerSpec
{
  public:
    CyclicTimerSpec();
    int periodMin() const;
    int periodMax() const;
    int defaultPeriod() const;
    int periodStep() const;
    int periodPageStep() const;

    int boundMin() const;
    int boundMax() const;
    int defaultStart() const;
    int defaultTerminate() const;
    int boundStep() const;
    int boundPageStep() const;

    int volumeMin() const;
    int volumeMax() const;
    int defaultVolume() const;
    int volumeStep() const;
    int volumePageStep() const;

  private:
    Q_DISABLE_COPY(CyclicTimerSpec)
    int PeriodMin = 5;
    int PeriodMax = 60 * 15;
    int DefaultPeriod = 30;
    int PeriodStep = 1;
    int PeriodPageStep = 30;

    int BoundMin = 0;
    int BoundMax = 60 * 15;
    int DefaultStart = 0;
    int DefaultTerminate = 0;
    int BoundStep = 1;
    int BoundPageStep = 30;

    int VolumeMin = 0;
    int VolumeMax = 100;
    int DefaultVolume = 100;
    int VolumeStep = 1;
    int VolumePageStep = 10;
};

#endif // CYCLIC_TIMER_SPEC_HPP
