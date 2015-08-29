#ifndef CYCLIC_TIMER_DATA_HPP
#define CYCLIC_TIMER_DATA_HPP

#include <QString>
#include <QKeySequence>

class CyclicTimer;

class CyclicTimerData
{
  friend class CyclicTimer;

  public:
    CyclicTimerData(int period, int start, int terminate, int volume, QString Sound, QKeySequence hotkey);
    bool enabled(); // useless ??
    int period();
    int start();
    int terminate();
    int volume();
    QString sound();
    QKeySequence hotkey();

  private:
    bool Enabled;
    int Period;
    int Start;
    int Terminate;
    int Volume;
    QString Sound;
    QKeySequence Hotkey;
};

#endif // CYCLIC_TIMER_DATA_HPP
