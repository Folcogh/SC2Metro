//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef DLGEDITTIMER_HPP
#define DLGEDITTIMER_HPP

#include "HotkeyInputWidget.hpp"
#include "SMDialog.hpp"
#include <QString>
#include <QSpinBox>
#include <QFormLayout>
#include <QKeySequence>
#include <QDialogButtonBox>

class DlgEditTimer : public SMDialog
{
    Q_DISABLE_COPY(DlgEditTimer)

  public:
    DlgEditTimer(QString filename, int period, QKeySequence keySequence, UINT modifiers, UINT virtualKey, QWidget* parent = nullptr);

    // Getters used by the caller to retrieve user inputs
    int getPeriod() const { return editPeriod->value(); }
    QKeySequence getKeySquence() const { return editHotkey->getKeySequence(); }
    UINT getNativeVirtualKey() const { return editHotkey->getNativeVirtualKey(); }
    UINT getNativeModifiers() const { return editHotkey->getNativeModifiers(); }
  private:
    // Elements of the ui which are used by some slots
    QSpinBox* editPeriod;
    HotkeyInputWidget* editHotkey;
    QDialogButtonBox* buttons;
    QFormLayout* formLayout;

    // Slots
    void periodModified(int period);
    void hotkeyModified();
};

#endif // DLGEDITTIMER_HPP
