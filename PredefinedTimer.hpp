//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef PREDEFINEDTIMER_HPP
#define PREDEFINEDTIMER_HPP

#include <QString>
#include <QMetaType>
#include <QKeySequence>

#define CUSTOM_TIMER true
#define CUSTOM_TIMER_PERIOD 30
#define CUSTOM_TIMER_NAME "<Custom...>"

//
//  This class contains a predefined timer used to be proposed
//  in the list when the user creates a new timer
//

class PredefinedTimer
{
    public:
        PredefinedTimer(QString soundfile, int period, QKeySequence shortcut, bool custom = false);

        // Getters
        QString getName() const;
        QString getSoundFile() const;
        int getPeriod() const;
        QKeySequence getShortcut() const;
        bool isCustom() const;

    private:
        Q_DISABLE_COPY(PredefinedTimer)

        // Data of a timer
        QString soundFile;
        int period;
        QKeySequence shortcut;

        // Name displayed in the combo box. It's build from the file name
        QString name;

        // Used by the combo box to know how to handle the selected item
        bool custom = false;
};

// PredefinedTimer* may be stored as a QVariant
Q_DECLARE_METATYPE(PredefinedTimer*)

#endif // PREDEFINEDTIMER_HPP
