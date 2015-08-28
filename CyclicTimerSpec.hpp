#ifndef CYCLIC_TIMER_SPEC_HPP
#define CYCLIC_TIMER_SPEC_HPP

class CyclicTimerSpec
{
  public:
    int periodMin() const { return PeriodMin; }
    int periodMax() const { return PeriodMax; }
    int defaultPeriod() const { return DefaultPeriod; }
    int periodStep() const { return PeriodStep; }
    int periodPageStep() const { return PeriodPageStep; }

    int boundMin() const { return BoundMin; }
    int boundMax() const { return BoundMax; }
    int defaultStart() const { return DefaultStart; }
    int defaultTerminate() const { return DefaultTerminate; }
    int boundStep() const { return BoundStep; }
    int boundPageStep() const { return BoundPageStep; }

    int volumeMin() const { return VolumeMin; }
    int volumeMax() const { return VolumeMax; }
    int defaultVolume() const { return DefaultVolume; }
    int volumeStep() const { return VolumeStep; }
    int volumePageStep() const { return VolumePageStep; }

   private:
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
