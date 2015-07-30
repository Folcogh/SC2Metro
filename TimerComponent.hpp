// Folco's Metronome for SC2.
// Copyright (C) 2015  Martial Demolins AKA Folco

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef TIMERCOMPONENT_HPP
#define TIMERCOMPONENT_HPP

#include <QObject>
#include <QString>

#define CREEP_PERIOD 33
#define INJECT_PERIOD 44
#define MINIMAP_PERIOD 10
#define WORKER_PERIOD 17
#define CUSTOM_PERIOD 30

// This class provides default data for each predefined timer

class TimerComponent : public QObject
{
    Q_OBJECT
  public:
    TimerComponent(QObject* parent, QString name, QString fullfilename,
                   int period, bool custom);
    QString name() const;
    QString fullfilename() const;
    int period() const;
    bool custom() const;
    void setFilename(QString filename);
    void setPeriod(int period);

  private:
    Q_DISABLE_COPY(TimerComponent)
    QString m_name;         // Used in the combo of predefined timers
    QString m_fullfilename; // Sound of the timer
    int m_period;           // Default period
    bool m_custom;          // False if the timer is a predefined one
};

#endif // TIMERCOMPONENT_HPP
