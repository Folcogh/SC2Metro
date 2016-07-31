//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
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
    , shortcut(QKeySequence())
    , nativeVirtualKey(0)
    , nativeModifiers(0)
    , promptForFile(true)
{
    this->displayedName = QObject::tr("<Custom...>");
}

// Create an item with a filename given by the user, with a default period and no shortcut
TimerItem::TimerItem(QString filename)
    : TimerItem(filename, CUSTOM_TIMER_PERIOD, QKeySequence(), 0, 0)
{
}

// Create an item with all values defined. Used for builtin items
TimerItem::TimerItem(QString filename, int period, QKeySequence shortcut, UINT nativeVirtualKey, UINT nativeModifiers)
    : filename(filename)
    , period(period)
    , shortcut(shortcut)
    , nativeVirtualKey(nativeVirtualKey)
    , nativeModifiers(nativeModifiers)
    , promptForFile(false)
{
    QFileInfo info(filename);
    this->displayedName = info.completeBaseName();
}

QString TimerItem::getDisplayedName() const
{
    return this->displayedName;
}

QString TimerItem::getFilename() const
{
    return this->filename;
}

int TimerItem::getPeriod() const
{
    return this->period;
}

QKeySequence TimerItem::getShortcut() const
{
    return this->shortcut;
}

UINT TimerItem::getNativeVirtualKey() const
{
    return this->nativeVirtualKey;
}

UINT TimerItem::getNativeModifiers() const
{
    return this->nativeModifiers;
}

bool TimerItem::mustPromptForFile() const
{
    return this->promptForFile;
}
