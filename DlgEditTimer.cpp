//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "DlgEditTimer.hpp"
#include "Timer.hpp"
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeySequenceEdit>

DlgEditTimer::DlgEditTimer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers, QWidget* parent)
    : QDialog(parent)
{
    // Remove the '?' button
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // Build the form layout which contains input widgets
    this->editPeriod = new QSpinBox;
    this->editHotkey = new HotkeyInputWidget;

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(tr("Period:"), this->editPeriod);
    formLayout->addRow(tr("Hotkey"), this->editHotkey);

    // Label containing the filename of the timer to edit
    QLabel* labelFilename = new QLabel(filename, this);

    // The label displayed if an hotkey is invalid. It's red, an invisible by default
    this->labelInvalidHotkey = new QLabel(tr("Invalid hotkey"));
    this->labelInvalidHotkey->setStyleSheet("QLabel { color : red; }");

    // OK/Cancel buttons
    this->buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Period parameters
    this->editPeriod->setRange(PERIOD_MIN, PERIOD_MAX);
    this->editPeriod->setAlignment(Qt::AlignHCenter);

    // Set default values
    this->editPeriod->setValue(period);
    this->editHotkey->setHotkey(keySequence, virtualKey, modifiers);

    // Finalize the ui setup by placing the elements and adjusting their size
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(labelFilename);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(this->labelInvalidHotkey);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(this->buttons);
    setLayout(mainLayout);
    adjustSize();

    // Connections.
    connect(this->buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this->editHotkey, &QKeySequenceEdit::keySequenceChanged, this, &DlgEditTimer::hotkeyModified);
    connect(this->editPeriod, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DlgEditTimer::periodModified);

    // Trigger the slots to refresh the ui
    periodModified(period);
    hotkeyModified();
}

DlgEditTimer::~DlgEditTimer() {}
//
//  Slots
//

// Adjust the plural of "second" when the period input is modified
void DlgEditTimer::periodModified(int period)
{
    QString suffix = (period == 1 ? tr(" second") : tr(" seconds"));
    this->editPeriod->setSuffix(suffix);
}

// Set the OK button according to the existence of a valid hotkey
void DlgEditTimer::hotkeyModified()
{
    QPushButton* buttonOk = this->buttons->button(QDialogButtonBox::Ok);
    if (this->editHotkey->getNativeVirtualKey() != 0) {
        buttonOk->setEnabled(true);
        this->labelInvalidHotkey->setVisible(false);
    }
    else {
        buttonOk->setDisabled(true);
        this->labelInvalidHotkey->setVisible(true);
    }
}
