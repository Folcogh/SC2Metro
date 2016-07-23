//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef DLGNEWTIMER_HPP
#define DLGNEWTIMER_HPP

#include <QDialog>
#include <QString>
#include <QKeySequence>
#include "PredefinedTimer.hpp"

namespace Ui {
class DlgNewTimer;
}

//
//  This class prompts a dialog requesting a sound, a period and a shortcut.
//  The sound, period and shortcut are accessible with getters when the dialog is closed
//

class DlgNewTimer: public QDialog
{
    Q_OBJECT

    public:
        explicit DlgNewTimer(QWidget *parent = 0);
        ~DlgNewTimer();

        // Getters
        QString getSound() const;
        int getPeriod() const;
        QKeySequence getShortcut() const;

    private:
        Q_DISABLE_COPY(DlgNewTimer)
        Ui::DlgNewTimer *ui;

        // Methods used by the constructor to build the sound combo box
        void addPredefinedTimer(QString file, int period, int shortcut);
        void addCustomTimer();

        // Slots
        void soundModified();
        void checkOKButton();
        void truncateShortcut();

        // Shortcut
        PredefinedTimer* getCurrentTimer() const;
        void refreshUi();

        // Store the previous path used to get a custom sound,
        // to make the selection of multiple custom sounds easier
        static QString previousPath;

        // Used by the sound combo if the user cancels a custom sound selection
        int previousIndex;
};

#endif // DLGNEWTIMER_HPP
