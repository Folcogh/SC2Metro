//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "DlgNewTimer.hpp"
#include "ui_DlgNewTimer.h"
#include "SC2Metro.hpp"
#include "Timer.hpp"
#include <QDir>
#include <QVariant>
#include <QFileInfo>
#include <QFileDialog>
#include <QPushButton>
#include <QKeySequenceEdit>

QString DlgNewTimer::previousPath = QDir::homePath();

DlgNewTimer::DlgNewTimer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgNewTimer)
{
    ui->setupUi(this);

    // Add the timers to the ui
    addPredefinedTimer(":/sounds/minimap.mp3", 10, Qt::ALT + Qt::SHIFT + Qt::Key_M);
    addPredefinedTimer(":/sounds/scout.mp3", 60*3, Qt::ALT + Qt::SHIFT + Qt::Key_S);
    addPredefinedTimer(":/sounds/resource.mp3", 30, Qt::ALT + Qt::SHIFT + Qt::Key_R);
    addPredefinedTimer(":/sounds/supply.mp3", 30, Qt::ALT + Qt::SHIFT + Qt::Key_P);
    addPredefinedTimer(":/sounds/creep.mp3", 24, Qt::ALT + Qt::SHIFT + Qt::Key_C);
    addPredefinedTimer(":/sounds/inject.mp3", 33, Qt::ALT + Qt::SHIFT + Qt::Key_I);
    addPredefinedTimer(":/sounds/worker.mp3", 12, Qt::ALT + Qt::SHIFT + Qt::Key_W);
    addPredefinedTimer(":/sounds/mule.mp3", 64, Qt::ALT + Qt::SHIFT + Qt::Key_L);
    addCustomTimer();

    // Remember the current index
    previousIndex = ui->comboSound->currentIndex();

    // Complete the ui
    setMinimumWidth(250);
    ui->spinPeriod->setMaximum(TIMER_MAX_VALUE);
    refreshUi();
    checkOKButton();
    adjustSize();

    // Connections
    connect(ui->buttonOK, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->editShortcut, &QKeySequenceEdit::keySequenceChanged, this, &DlgNewTimer::checkOKButton);
    connect(ui->comboSound, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &DlgNewTimer::soundModified);
    connect(ui->editShortcut, &QKeySequenceEdit::editingFinished, this, &DlgNewTimer::truncateShortcut);
}

DlgNewTimer::~DlgNewTimer()
{
    for (int i = 0; i < ui->comboSound->count(); i++) {
        QVariant timer = ui->comboSound->itemData(i);
        delete timer.value<PredefinedTimer*>();
    }
    delete ui;
}

//
//  Methods used by the constructor to add the built-in timers to the list
//

void DlgNewTimer::addPredefinedTimer(QString file, int period, int shortcut)
{
    QKeySequence shortcutKeys = QKeySequence(shortcut);
    PredefinedTimer* timer = new PredefinedTimer(file, period, shortcutKeys);
    QString timerName = timer->getName();
    QVariant data = QVariant::fromValue(timer);

    ui->comboSound->addItem(timerName, data);
}

void DlgNewTimer::addCustomTimer()
{
    PredefinedTimer* timer = new PredefinedTimer("", CUSTOM_TIMER_PERIOD, QKeySequence(), CUSTOM_TIMER); \
    QString timerName = timer->getName();
    QVariant data = QVariant::fromValue(timer);

    ui->comboSound->addItem(timerName, data);
}

//
//  Getters
//

QString DlgNewTimer::getSound() const
{
    return getCurrentTimer()->getSoundFile();
}

int DlgNewTimer::getPeriod() const
{
    return ui->spinPeriod->value();
}

QKeySequence DlgNewTimer::getShortcut() const
{
    return ui->editShortcut->keySequence();
}

//  The OK button is disabled if no shortcut is defined
void DlgNewTimer::checkOKButton()
{
    bool shortcutDefined = !ui->editShortcut->keySequence().isEmpty();

    ui->buttonOK->setEnabled(shortcutDefined);
}

// Synchronize the ui with the sound selection
void DlgNewTimer::refreshUi()
{
    PredefinedTimer* timer = getCurrentTimer();
    int period = timer->getPeriod();
    QKeySequence shortcut = timer->getShortcut();

    ui->spinPeriod->setValue(period);
    ui->editShortcut->setKeySequence(shortcut);
}

PredefinedTimer* DlgNewTimer::getCurrentTimer() const
{
    int index = ui->comboSound->currentIndex();
    QVariant data = ui->comboSound->itemData(index);

    return data.value<PredefinedTimer*>();
}

void DlgNewTimer::soundModified()
{
    // Block the events of the combo sound to prevent recursive call when modifying it
    ui->comboSound->blockSignals(true);

    // Get the current timer
    PredefinedTimer* timer = getCurrentTimer();

    // In the case of the custom timer:
    // - the user has to manually choose a sound
    // - the new item is added in the combo list
    if (timer->isCustom()) {
        QString file = QFileDialog::getOpenFileName(this, tr("Choose a sound file"), this->previousPath, tr("Sound (" SOUND_FILTER ")"));
        if (file.isEmpty()) {
            // File selection canceled, reset the timer change
            ui->comboSound->setCurrentIndex(this->previousIndex);
        }
        else {
            // File selection validated, save the file path and add the new timer to the combo
            this->previousPath = QFileInfo(file).absoluteFilePath();
            PredefinedTimer* newTimer = new PredefinedTimer(file, timer->getPeriod(), timer->getShortcut());
            ui->comboSound->insertItem(ui->comboSound->currentIndex(), newTimer->getName(), QVariant::fromValue(newTimer));
            ui->comboSound->setCurrentIndex(ui->comboSound->count() - 2);
        }
    }

    // Update the ui, save the current index and restore events handling
    refreshUi();
    this->previousIndex = ui->comboSound->currentIndex();
    ui->comboSound->blockSignals(false);
}

//
// Forbid a key sequence to contain more than one key combination
//
void DlgNewTimer::truncateShortcut()
{
    int value = ui->editShortcut->keySequence()[0];
    QKeySequence shortcut(value);
    ui->editShortcut->setKeySequence(shortcut);
}
