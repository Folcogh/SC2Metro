//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef HOTKEYINPUTWIDGET_HPP
#define HOTKEYINPUTWIDGET_HPP

#include <QEvent>
#include <QObject>
#include <windows.h>
#include <QKeySequence>
#include <QKeySequenceEdit>

#define QtKeysMask 0x01FFFFFF // All Qt keys without modifiers. See Qt::Key enum

/*
 *  This class modifies the keyboard handler of QKeySequenceEdit
 *  It intercepts the event to get the native modifiers and virtual key, needed for windows to register a hotkey
 *  It also allows to forbid some hotkeys, and limits the key sequence to one entry
 */

class HotkeyInputWidget : public QKeySequenceEdit
{
    Q_OBJECT

  public:
    HotkeyInputWidget();
    ~HotkeyInputWidget();

    // Getters
    QKeySequence getSequence() const;
    UINT getNativeVirtualKey() const;
    UINT getNativeModifiers() const;

    // Setter used by the parent dialog to change the sequence and the native key codes accordingly
    void setHotkey(QKeySequence sequence, UINT nativeVirtualKey, UINT nativeModifiers);

  private:
    bool eventFilter(QObject* object, QEvent* event) override;
    void truncateHotkey();
    UINT nativeModifiers;
    UINT nativeVirtualKey;
};

#endif // HOTKEYINPUTWIDGET_HPP
