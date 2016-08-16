//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "TimerItem.hpp"
#include <QFileInfo>

// Create an undefined item, which allow the user to add its own sound to the list
TimerItem::TimerItem()
    : filename(QString())
    , period(0)
    , keySequence(QKeySequence())
    , nativeModifiers(0)
    , nativeVirtualKey(0)
    , promptForFile(true)
{
    this->displayedName = QObject::tr("<Custom...>");
}

// Create an item with a filename given by the user, with a default period and no hotkey
TimerItem::TimerItem(QString filename)
    : TimerItem(filename, CUSTOM_TIMER_PERIOD, QKeySequence(), 0, 0)
{
}

// Create an item with all values defined. Used for builtin items
TimerItem::TimerItem(QString filename, int period, QKeySequence keySequence, UINT nativeModifiers, UINT nativeVirtualKey)
    : filename(filename)
    , period(period)
    , keySequence(keySequence)
    , nativeModifiers(nativeModifiers)
    , nativeVirtualKey(nativeVirtualKey)
    , promptForFile(false)
{
    QFileInfo info(filename);
    this->displayedName = info.completeBaseName();
}
