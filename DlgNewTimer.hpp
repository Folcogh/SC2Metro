//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef DLGNEWTIMER_HPP
#define DLGNEWTIMER_HPP

#include "HotkeyInputWidget.hpp"
#include "TimerItem.hpp"
#include <QLabel>
#include <QDialog>
#include <QObject>
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <windows.h>
#include <QKeySequence>
#include <QDialogButtonBox>

/*
 *  This class provides a dialog which requests for a new Timer.
 *  It uses the data of TimerItem instances to fill the ui.
 *  Then the interface is handled with its own data,
 *  without updating the TimerItem ones
 */

class DlgNewTimer : public QDialog
{
    Q_OBJECT

  public:
    explicit DlgNewTimer(QWidget* parent = nullptr);

    // Getters
    QString getFilename() const { return getCurrentTimerItem()->getFilename(); }
    int getPeriod() const { return editPeriod->value(); }
    QKeySequence getKeySquence() const { return editHotkey->getKeySequence(); }
    UINT getNativeVirtualKey() const { return editHotkey->getNativeVirtualKey(); }
    UINT getNativeModifiers() const { return editHotkey->getNativeModifiers(); }

  private:
    Q_DISABLE_COPY(DlgNewTimer)

    // Method used by the constructor to fill the sound combo box
    void addTimerItem();
    void addTimerItem(QString file, int period, int keys, UINT nativeModifiers, UINT nativeVirtualKey);

    // General purpose method
    TimerItem* getCurrentTimerItem() const { return timerList->currentData().value<TimerItem*>(); }

    // Widget containing user data
    QComboBox* timerList;
    QSpinBox* editPeriod;
    HotkeyInputWidget* editHotkey;
    QDialogButtonBox* buttons;
    QLabel* labelInvalidHotkey;

    // Convenient storages
    int previousIndex;
    static QString previousPath;

    // Slots
    void soundModified();
    void periodModified(int period);
    void hotkeyModified();
};

#endif // DLGNEWTIMER_HPP
