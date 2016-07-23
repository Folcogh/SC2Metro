//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef DLGMISC_HPP
#define DLGMISC_HPP

#include <QDialog>

namespace Ui {
class DlgMisc;
}

class DlgMisc: public QDialog
{
        Q_OBJECT

    public:
        explicit DlgMisc(QWidget *parent = 0);
        ~DlgMisc();

    private:
        Ui::DlgMisc *ui;
};

#endif // DLGMISC_HPP
