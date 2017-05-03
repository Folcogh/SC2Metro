//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "NativeEventFilter.hpp"
#include "windows.h"
#include <QCoreApplication>

NativeEventFilter::NativeEventFilter()
{
    //
    QCoreApplication::instance()->installNativeEventFilter(this);
}

// Receive native Windows event and emit a message containing the hotkey ID
bool NativeEventFilter::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
{
    (void)result;
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {
            emit hotkeyReceived(msg->wParam);
        }
    }
    return false;
}

//CAN SOMEONE TELL ME HOW IT WORKS? WHAT HOTKEYS IT LOOKING FOR?
