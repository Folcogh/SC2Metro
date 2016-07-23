//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMER_HPP
#define TIMER_HPP

#include <QObject>
#include <QString>
#include <QMetaType>
#include <QKeySequence>

#define TIMER_MAX_VALUE 10*60

class Timer
{
    public:
        Timer(QString filename, int period, QKeySequence shortcut, int id);
        ~Timer();

        QString getName() const;
        int getPeriod() const;
        QKeySequence getShortcut() const;

        bool setPeriod(int period);
        bool setShortcut(QKeySequence shortcut, int id);

        unsigned int getKeyId();
        void togglePlayStop();

    private:
        Q_DISABLE_COPY(Timer)

        QString filename;
        int period;
        QKeySequence shortcut;

        // Hotkey stuff
        unsigned int keyId;
        void unregisterHotkey();
        void registerHotkey(QKeySequence shortcut, int id);
};

// Timer* may be stored as a QVariant
Q_DECLARE_METATYPE(Timer*)

#endif // TIMER_HPP
