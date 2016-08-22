//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "HotkeyInputWidget.hpp"
#include <QKeyEvent>

// The data are initialized to 0, accordingly to an empty QKeySequenceEdit
HotkeyInputWidget::HotkeyInputWidget()
    : nativeVirtualKey(0)
    , nativeModifiers(0)
{
    this->installEventFilter(this);
}

void HotkeyInputWidget::setHotkey(QKeySequence keySequence, UINT nativeModifiers, UINT nativeVirtualKey)
{
    this->nativeModifiers  = nativeModifiers;
    this->nativeVirtualKey = nativeVirtualKey;

    // Set the key sequence after the native keys, to ensure consistent data
    // when the QKeySequence::keySequenceChanged event is emitted
    setKeySequence(keySequence);
}


// This keyboard event handler replaces the original one
bool HotkeyInputWidget::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // Read the keys
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        int key                         = keyEvent->key() & QtKeysMask;
        UINT virtualKey                 = keyEvent->nativeVirtualKey();

        // Reset the modifiers then read them
        this->nativeModifiers = 0;

        if (modifiers & Qt::CTRL) {
            this->nativeModifiers |= MOD_CONTROL;
            if (key == Qt::Key_Control) {
                key = 0;
            }
        }
        if (modifiers & Qt::ALT) {
            this->nativeModifiers |= MOD_ALT;
            if (key == Qt::Key_Alt) {
                key = 0;
            }
        }
        if (modifiers & Qt::SHIFT) {
            this->nativeModifiers |= MOD_SHIFT;
            if (key == Qt::Key_Shift) {
                key = 0;
            }
        }

        // Invalid hotkeys, stoping the keyboard handling:
        // - all which involve the Meta key (reserved by the system)
        // - events with no modifiers
        // - events with no key
        if ((modifiers & Qt::META) || (modifiers == 0) || (key == 0)) {
            return true;
        }

        // If there is already a key sequence, and if it has been validly defined,
        // clear it to enter a new one
        if (!keySequence().isEmpty() && (this->nativeVirtualKey != 0)) {
            clear();
        }
        this->nativeVirtualKey = virtualKey;
    }

    return QObject::eventFilter(object, event);
}
