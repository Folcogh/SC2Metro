#ifndef CYCLIC_TIMER_VIEW_DATA_HPP
#define CYCLIC_TIMER_VIEW_DATA_HPP

#include <QKeySequence>

typedef struct CYCLIC_TIMER_VIEW_DATA
{
    QString filename;
    int period;
    int start;
    int end;
    QKeySequence hotkey;
    int volume;
} CYCLIC_TIMER_VIEW_DATA;

#endif // CYCLIC_TIMER_VIEW_DATA_HPP
