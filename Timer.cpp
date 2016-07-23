//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "Timer.hpp"
#include "windows.h"
#include "KeyTranslator.hpp"
#include <QObject>
#include <QFileInfo>

Timer::Timer(QString filename, int period, QKeySequence shortcut, int id)
    : filename(filename)
    , period(period)
    , shortcut(shortcut)
    , keyId(0)
{
    registerHotkey(shortcut, id);
}

Timer::~Timer()
{
    unregisterHotkey();
}

QString Timer::getName() const
{
    return this->filename;
}

int Timer::getPeriod() const
{
    return this->period;
}

QKeySequence Timer::getShortcut() const
{
    return this->shortcut;
}

bool Timer::setPeriod(int period)
{
    if (this->period == period) {
        return false;
    }
    this->period = period;
    return true;
}

bool Timer::setShortcut(QKeySequence shortcut, int id)
{
    // Early return if no change to perform
    if (this->shortcut == shortcut) {
        return false;
    }

    unregisterHotkey();
    registerHotkey(shortcut, id);
    this->shortcut = shortcut;
    return true;
}

unsigned int Timer::getKeyId()
{
    return this->keyId;
}

void Timer::togglePlayStop()
{

}

void Timer::unregisterHotkey()
{
    if (this->keyId != 0) {
        UnregisterHotKey(nullptr, this->keyId);
    }
}

void Timer::registerHotkey(QKeySequence shortcut, int id)
{
    unsigned int modifiers;
    unsigned int virtualKey;
    KeyTranslator::translateKey(shortcut[0], &modifiers, &virtualKey);
    RegisterHotKey(nullptr, id, modifiers, virtualKey);
}
