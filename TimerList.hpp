#ifndef TIMERLIST_HPP
#define TIMERLIST_HPP

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
};

#endif // TIMERLIST_HPP
