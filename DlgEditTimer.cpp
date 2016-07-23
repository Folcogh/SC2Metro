//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "DlgEditTimer.hpp"
#include "ui_DlgEditTimer.h"
#include "SC2Metro.hpp"
#include "Timer.hpp"
#include <QChar>
#include <QDialog>
#include <QSpinBox>
#include <QFileInfo>
#include <QPushButton>
#include <QKeySequence>
#include <QKeySequenceEdit>

DlgEditTimer::DlgEditTimer(QString name, int period, QKeySequence shortcut)
    : ui(new Ui::DlgEditTimer)
{
    ui->setupUi(this);
    connect(ui->buttonOK, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->editShortcut, &QKeySequenceEdit::editingFinished, this, &DlgEditTimer::truncateShortcut);

    // Create the displayed name
    QFileInfo finfo(name);
    QString displayedName = finfo.completeBaseName();
    if (name.at(0) == QChar(':')) {
        displayedName.append(BUILTIN_TAG);
    }

    // Update ui
    ui->labelDispSound->setText(displayedName);
    ui->spinPeriod->setMaximum(TIMER_MAX_VALUE);
    ui->spinPeriod->setValue(period);
    ui->editShortcut->setKeySequence(shortcut);
    adjustSize();
    setMinimumWidth(250);
}

DlgEditTimer::~DlgEditTimer()
{
    delete ui;
}

//
// Forbid a key sequence to contain more than one key combination
//
void DlgEditTimer::truncateShortcut()
{
    int value = ui->editShortcut->keySequence()[0];
    QKeySequence shortcut(value);
    ui->editShortcut->setKeySequence(shortcut);
}

int DlgEditTimer::getPeriod() const
{
    return ui->spinPeriod->value();
}

QKeySequence DlgEditTimer::getShortcut() const
{
    return ui->editShortcut->keySequence();
}
