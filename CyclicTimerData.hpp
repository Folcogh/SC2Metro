#ifndef CYCLIC_TIMER_DATA_HPP
#define CYCLIC_TIMER_DATA_HPP

#include <QString>
#include <QKeySequence>

class CyclicTimerData
{
  public:
      CyclicTimerData(int period, int start, int terminate, int volume, QString sound, QKeySequence hotkey)
      : Period(period), Start(start), Terminate(terminate), Volume(volume), Sound(sound), Hotkey(hotkey) {};
      int period() const { return Period; }
      int start() const { return Start; }
      int terminate() const { return Terminate; }
      int volume() const { return Volume; }
      QString sound() const { return Sound; }
      QKeySequence hotkey() const { return Hotkey; }

  private:
      int Period;
      int Start;
      int Terminate;
      int Volume;
      QString Sound;
      QKeySequence Hotkey;
};

#endif // CYCLIC_TIMER_DATA_HPP
