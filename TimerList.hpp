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

    private:
        Q_DISABLE_COPY(TimerList)

        // TimerList is a singleton
        static TimerList* timerList;
        TimerList();

        QList<Timer*> timers;
};

#endif // TIMERLIST_HPP
