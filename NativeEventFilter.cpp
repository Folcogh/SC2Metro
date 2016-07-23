//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "NativeEventFilter.hpp"
#include "MainWindow.hpp"
#include "Timer.hpp"
#include <QVariant>
#include <windows.h>
#include <QTableWidgetItem>

NativeEventFilter::NativeEventFilter(QTableWidget* table)
    : table(table)
{
}

NativeEventFilter::~NativeEventFilter()
{
}

bool NativeEventFilter::nativeEventFilter(const QByteArray& eventType, void* message, long*)
{
    // Return false if the event musn't be filtered, true if it's a real hotkey event
    bool retval = false;

    if (eventType == "windows_dispatcher_MSG") {
        MSG* msg = static_cast<MSG*>(message); // TODO: use only lower word ? See https://msdn.microsoft.com/fr-fr/library/windows/desktop/ms644958(v=vs.85).aspx
        if (msg->message == WM_HOTKEY) {
            // Hotkey received. Parse the table to know if a timer has registered this key
            for (int i = 0; i < table->rowCount(); i++) {
                QTableWidgetItem* item = table->item(i, DATA_COLUMN);
                QVariant data = item->data(TIMER_PTR);
                Timer* timer = data.value<Timer*>();

                if (msg->wParam == timer->getKeyId()) {
                    timer->togglePlayStop();
                    retval = true;
                }
            }
        }
    }
    return retval;
}
