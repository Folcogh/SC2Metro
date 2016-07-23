#include "TimerList.hpp"
#include "MainWindow.hpp"

TimerList* TimerList::timerList = nullptr;

TimerList::TimerList()
{

}

TimerList::~TimerList()
{
    this->timerList = nullptr;
}

TimerList*TimerList::instance()
{
    if (timerList == nullptr) {
        timerList = new TimerList;
    }
    return timerList;
}
