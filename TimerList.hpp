#ifndef TIMERLIST_HPP
#define TIMERLIST_HPP

#include "Timer.hpp"
#include <QList>
#include <QObject>

class TimerList: public QObject
{
        Q_OBJECT

    public:
        ~TimerList();
        static TimerList* instance();

        // Methods called by the ui's actions using connections
        void newTimer();

    private:
        Q_DISABLE_COPY(TimerList)

        // TimerList is a singleton
        static TimerList* timerList;
        TimerList();

        // The list of the timers ptr. It's ordered like the table of the ui
        QList<Timer*> timers;
};

#endif // TIMERLIST_HPP
