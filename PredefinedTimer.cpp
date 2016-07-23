//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "PredefinedTimer.hpp"
#include <QFileInfo>

PredefinedTimer::PredefinedTimer(QString soundfile, int period, QKeySequence shortcut, bool custom)
    : soundFile(soundfile)
    , period(period)
    , shortcut(shortcut)
    , custom(custom)
{
    // The name is built from the filename for a predefined timer, else it's generic
    if (custom) {
        this->name = CUSTOM_TIMER_NAME;
    }
    else {
        QFileInfo info(soundfile);
        this->name = info.completeBaseName();
    }
}

QString PredefinedTimer::getName() const
{
    return this->name;
}

QString PredefinedTimer::getSoundFile() const
{
    return this->soundFile;
}

int PredefinedTimer::getPeriod() const
{
    return this->period;
}

QKeySequence PredefinedTimer::getShortcut() const
{
    return this->shortcut;
}

bool PredefinedTimer::isCustom() const
{
    return this->custom;
}
