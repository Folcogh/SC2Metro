#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>

#define PERIOD_MIN 1
#define PERIOD_MAX 600

class Timer
{
    public:
        Timer();
        ~Timer();

    private:
        Q_DISABLE_COPY(Timer)
};

#endif // TIMER_HPP
