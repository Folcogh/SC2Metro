//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "SMException.hpp"
#include "MainWindow.hpp"
#include "TimerList.hpp"
#include <QFileInfo>
#include <QMessageBox>
#include <QApplication>

TimerList* TimerList::timerList = nullptr;

TimerList::TimerList()
    : hotkeyId(1)
{
}

TimerList::~TimerList()
{
    this->timerList = nullptr;
}

TimerList* TimerList::instance()
{
    if (timerList == nullptr) {
        timerList = new TimerList;
    }
    return timerList;
}

bool TimerList::hotkeyReceived(WPARAM keyId)
{
    for (int i = 0; i < this->timers.count(); i++) {
        Timer* timer = this->timers.at(i);
        if (timer->getHotkeyId() == keyId) {
            if (timer->togglePlayStop()) {
                MainWindow::instance()->setTimerPlaying(i);
            }
            else {
                MainWindow::instance()->setTimerStopped(i);
            }
            return true;
        }
    }
    return false;
}

void TimerList::newTimer(QString filename, int period, QKeySequence keySequence, UINT virtualKey, UINT modifiers)
{
    try {
        Timer* timer = new Timer(filename, period, keySequence, virtualKey, modifiers, this->hotkeyId);
        this->hotkeyId++;
        MainWindow::instance()->newTimer(filename, period, keySequence);

        this->timers.append(timer);
    }
    catch (const SMException& exc) {
        QString readableFilename = QFileInfo(filename).completeBaseName();
        QString message          = QString(tr("Failed to add the timer %1. Reason: %2")).arg(readableFilename).arg(exc.getMessage());
        QMessageBox::critical(MainWindow::instance(), tr("Error"), message, QMessageBox::Ok);
        return;
    }
}
