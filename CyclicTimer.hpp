#ifndef CYCLICTIMER_HPP
#define CYCLICTIMER_HPP

#include <QString>
#include <QKeySequence>

class CyclicTimer
{
    public:
        CyclicTimer();

        void setSound(QString sound);
        void setPeriod(int period);
        void setStart(int start);
        void setTerminate(int terminate);
        void setVolume(int volume);
        void setHotkey(QKeySequence hotkey);

        QString getSound();
        int getPeriod();
        int getStart();
        int getTerminate();
        int getVolume();
        QKeySequence getHotkey();

    private:
        QString m_sound;
        int m_period;
        int m_start;
        int m_terminate;
        int m_volume;
        QKeySequence m_hotkey;
};

#endif // CYCLICTIMER_HPP
