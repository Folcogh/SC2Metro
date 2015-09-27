#ifndef CYCLIC_TIMER_DATA_HPP
#define CYCLIC_TIMER_DATA_HPP

#include <QString>
#include <QKeySequence>

class CyclicTimerData
{
  public:
    CyclicTimerData() {}
    CyclicTimerData(int period, int start, int terminate, int volume, QString Sound, QKeySequence hotkey);
    ~CyclicTimerData() {}
    bool enabled() const; // useless ??
    int period() const;
    int start() const;
    int terminate() const;
    int volume() const;
    QString sound() const;
    QKeySequence hotkey() const;

    void setEnabled(bool enabled);

  private:
    bool Enabled;
    int Period;
    int Start;
    int Terminate;
    int Volume;
    QString Sound;
    QKeySequence Hotkey;
};

namespace Role
{
    enum {CyclicTimerDataPointer = Qt::UserRole};
}

#endif // CYCLIC_TIMER_DATA_HPP
