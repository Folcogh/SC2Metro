//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMERLIST_HPP
#define TIMERLIST_HPP

#include "Timer.hpp"
#include <QList>
#include <QObject>
#include <QString>
#include <windows.h>
#include <QKeySequence>

/*
 *  This class is the container of the timers created by the user
 *
 */
class TimerList : public QObject
{
    Q_OBJECT

  public:
    ~TimerList();
    static TimerList* instance();
    bool hotkeyReceived(WPARAM keyId);

    void newTimer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers);

  private:
    Q_DISABLE_COPY(TimerList)

    // TimerList is a singleton
    static TimerList* timerList;
    TimerList();

    // The list of the timers ptr. It's ordered like the table of the ui
    QList<Timer*> timers;

    unsigned int hotkeyId;
};

#endif // TIMERLIST_HPP
