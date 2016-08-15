//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "DlgNewTimer.hpp"
#include "SC2Metro.hpp"
#include "Timer.hpp"
#include <QDir>
#include <QFileDialog>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QKeySequenceEdit>

// Initial path of the custom sound selection dialog. previousPath stores the last used one
QString DlgNewTimer::previousPath = QDir::homePath();

DlgNewTimer::DlgNewTimer(QWidget* parent)
    : QDialog(parent)
{
    // Build the form layout which contains input widgets
    this->timerList  = new QComboBox;
    this->editPeriod = new QSpinBox;
    this->editHotkey = new HotkeyInputWidget;

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow(tr("Sound file:"), this->timerList);
    formLayout->addRow(tr("Period:"), this->editPeriod);
    formLayout->addRow(tr("Hotkey"), this->editHotkey);

    // The label displayed if an hotkey is invalid. It's red, an invisible by default
    this->labelInvalidHotkey = new QLabel(tr("Invalid hotkey"));
    this->labelInvalidHotkey->setStyleSheet("QLabel { color : red; }");

    // OK/Cancel buttons
    this->buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // Period parameters
    this->editPeriod->setRange(PERIOD_MIN, PERIOD_MAX);
    this->editPeriod->setAlignment(Qt::AlignHCenter);

    // Create and add the items in the sound list
    addTimerItem("qrc:/sounds/minimap.mp3", 10, Qt::ALT + Qt::SHIFT + Qt::Key_M, 0x4D, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/scout.mp3", 60 * 3, Qt::ALT + Qt::SHIFT + Qt::Key_S, 0x53, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/resource.mp3", 30, Qt::ALT + Qt::SHIFT + Qt::Key_R, 0x52, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/supply.mp3", 30, Qt::ALT + Qt::SHIFT + Qt::Key_P, 0x50, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/creep.mp3", 24, Qt::ALT + Qt::SHIFT + Qt::Key_C, 0x43, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/inject.mp3", 33, Qt::ALT + Qt::SHIFT + Qt::Key_I, 0x49, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/worker.mp3", 12, Qt::ALT + Qt::SHIFT + Qt::Key_W, 0x57, MOD_ALT + MOD_SHIFT);
    addTimerItem("qrc:/sounds/mule.mp3", 64, Qt::ALT + Qt::SHIFT + Qt::Key_L, 0x4C, MOD_ALT + MOD_SHIFT);
    addTimerItem();

    // Finalize the ui setup by placing the elements and adjusting their size
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(this->labelInvalidHotkey);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(this->buttons);
    setLayout(mainLayout);
    adjustSize();

    // Set the previous index of the combo at the current one
    // It's used if the user cancels the choice of a custom sound
    this->previousIndex = this->timerList->currentIndex();

    // Connections.
    connect(this->buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(this->buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(this->editHotkey, &QKeySequenceEdit::keySequenceChanged, this, &DlgNewTimer::hotkeyModified);
    connect(this->editPeriod, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &DlgNewTimer::periodModified);
    connect(this->timerList, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated), this, &DlgNewTimer::soundModified);

    // Trigger the "sound modified" slot to refresh the ui
    soundModified();
}

DlgNewTimer::~DlgNewTimer()
{
}

//
//  Methods used by the constructor
//

// Add a "Custom" item to the sound list
void DlgNewTimer::addTimerItem()
{
    TimerItem* timerItem  = new TimerItem;
    QString displayedName = timerItem->getDisplayedName();
    QVariant data         = QVariant::fromValue(timerItem);

    this->timerList->addItem(displayedName, data);
}

// Add an item to the sound list
void DlgNewTimer::addTimerItem(QString file, int period, int keys, UINT nativeVirtualKey, UINT nativeModifiers)
{
    QKeySequence keySequence = QKeySequence(keys);
    TimerItem* timerItem     = new TimerItem(file, period, keySequence, nativeVirtualKey, nativeModifiers);
    QString displayedName    = timerItem->getDisplayedName();
    QVariant data            = QVariant::fromValue(timerItem);

    this->timerList->addItem(displayedName, data);
}


//
//  Slots
//

// Adjust the plural of "second" when the period input is modified
void DlgNewTimer::periodModified(int period)
{
    QString suffix = tr(" second");
    if (period > 1) {
        suffix = tr(" seconds");
    }
    this->editPeriod->setSuffix(suffix);
}

// Update the whole ui when the selected sound changes
void DlgNewTimer::soundModified()
{
    // Block the events of the combo sound to prevent recursive call when modifying it
    this->timerList->blockSignals(true);

    // In the case where "Custom timer" is selected
    // - the user has to manually choose a sound
    // - the new item is added in the combo list
    if (getCurrentTimerItem()->mustPromptForFile()) {
        QString filename = QFileDialog::getOpenFileName(this, tr("Choose a sound file"), this->previousPath, tr("Sound (" SOUND_FILTER ")"));
        if (filename.isEmpty()) {
            // File selection canceled, reset the timer change
            this->timerList->setCurrentIndex(this->previousIndex);
        }
        else {
            // File selection validated, save the file path and add the new timer to the combo
            this->previousPath      = QFileInfo(filename).absoluteFilePath();
            TimerItem* newTimerItem = new TimerItem(filename);
            this->timerList->insertItem(this->timerList->currentIndex(), newTimerItem->getDisplayedName(), QVariant::fromValue(newTimerItem));
            this->timerList->setCurrentIndex(this->timerList->count() - 2);
        }
    }

    // Update the ui, save the current index and restore events handling
    TimerItem* currentItem = getCurrentTimerItem();
    this->editPeriod->setValue(currentItem->getPeriod());
    this->editHotkey->setHotkey(currentItem->getKeySequence(), currentItem->getNativeVirtualKey(), currentItem->getNativeModifiers());

    this->previousIndex = this->timerList->currentIndex();
    this->timerList->blockSignals(false);
}

// Set the OK button according to the existence of a valid hotkey
void DlgNewTimer::hotkeyModified()
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
