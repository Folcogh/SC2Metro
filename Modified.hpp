//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef MODIFIED_HPP
#define MODIFIED_HPP

#include <QObject>

// This class is a boolean which emit a message when it is affected
class Modified : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Modified)

  public:
    Modified();
    bool isModified() const { return modified; }
    void setModified(bool modified);

  private:
    bool modified;

  signals:
    void changed(bool modified);
};

#endif // MODIFIED_HPP
