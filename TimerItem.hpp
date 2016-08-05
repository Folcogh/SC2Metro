//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMERITEM_HPP
#define TIMERITEM_HPP

#include <QString>
#include <QMetaType>
#include <windows.h>
#include <QKeySequence>

#define CUSTOM_TIMER_PERIOD 30

/*
 *  This class contains a predefined timer used to be proposed in the list when the user creates a new timer
 *  The data of the objects are used only to initialize the interface when their are displayed
 *
 */

class TimerItem {
  public:
    TimerItem();
    explicit TimerItem(QString filename);
    TimerItem(QString filename, int period, QKeySequence keySequence, UINT nativeVirtualKey, UINT nativeModifiers);

    // Getters
    QString getFilename() const;
    int getPeriod() const;
    QKeySequence getKeySequence() const;
    UINT getNativeVirtualKey() const;
    UINT getNativeModifiers() const;
    QString getDisplayedName() const;
    bool mustPromptForFile() const;

  private:
    Q_DISABLE_COPY(TimerItem)

    // Name displayed in the combo box. It's build from the file name
    QString displayedName;

    // Data of a timer
    QString filename;
    int period;
    QKeySequence keySequence;
    UINT nativeVirtualKey;
    UINT nativeModifiers;
    bool promptForFile;
};

// BuiltinTimerItem* may be stored as a QVariant
Q_DECLARE_METATYPE(TimerItem*)

#endif // TIMERITEM_HPP
