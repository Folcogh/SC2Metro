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

#include "TimerComponent.hpp"

TimerComponent::TimerComponent(QObject* parent, QString name, QString fullfilename, int period, bool custom)
    : QObject(parent)
    , m_name(name)
    , m_fullfilename(fullfilename)
    , m_period(period)
    , m_custom(custom)
{
}

QString TimerComponent::name() const
{
    return m_name;
}

QString TimerComponent::fullfilename() const
{
    return m_fullfilename;
}

int TimerComponent::period() const
{
    return m_period;
}

bool TimerComponent::custom() const
{
    return m_custom;
}

void TimerComponent::setFilename(QString path)
{
    m_fullfilename = path;
}

void TimerComponent::setPeriod(int period)
{
    m_period = period;
}
