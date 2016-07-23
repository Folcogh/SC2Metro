//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "KeyTranslator.hpp"
#include "windows.h"

#define SupportedModifiersMask 0x1E000000 // Support Shirt, Control, Alt and Meta
#define QtAllModifiersMask     0x7E000000 // All Qt modifiers
#define QtKeysMask             0x01FFFFFF // All Qt keys without modifiers

KeyTranslator::KeyTranslator()
{
}

// Check if a Qt key is translatable
bool KeyTranslator::isRegisterable(int key)
{
    // Check for valid modifiers
    if ((key & QtAllModifiersMask) != 0) {
        return false;
    }

    // Try to find a matching key
    key &= QtKeysMask;
    for (int i = 0; TranslationTable[i][0] != Qt::Key_unknown; i++) {
        if (TranslationTable[i][0] == key) {
            return true;
        }
    }
    return false;
}

// Translate a Qt key into Windows modifiers and virtual key. The key must be translatable
void KeyTranslator::translateKey(int key, unsigned int* modifiers, unsigned int* virtualKey)
{
    // Read modifiers
    unsigned qtModifiers = key &SupportedModifiersMask;

    // Set the MOD_NOREPEAT bit. FIXME: where is defined this macro?
    *modifiers = 0x4000;

    if (qtModifiers & Qt::ShiftModifier) {
        *modifiers |= MOD_SHIFT;
    }
    if (qtModifiers & Qt::ControlModifier) {
        *modifiers |= MOD_CONTROL;
    }
    if (qtModifiers & Qt::AltModifier) {
        *modifiers |= MOD_ALT;
    }
    if (qtModifiers & Qt::MetaModifier) {
        *modifiers |= MOD_WIN;
    }

    // Read key
    int qtKey = key & QtKeysMask;
    *virtualKey = Qt::Key_unknown; // Safety
    for (int i = 0; TranslationTable[i][0] != Qt::Key_unknown; i++) {
        if (qtKey == TranslationTable[i][0]) {
            *virtualKey = TranslationTable[i][1];
            break;
        }
    }
}

// Doc used:
// http://code.qt.io/cgit/qt/qtbase.git/tree/src/plugins/platforms/windows/qwindowskeymapper.cpp
// https://msdn.microsoft.com/fr-fr/library/windows/desktop/dd375731(v=vs.85).aspx
int KeyTranslator::TranslationTable[][2] =
{
    0x01000000,      VK_ESCAPE,   // Qt::Key_Escape
    0x01000001,      VK_TAB,      // Qt::Key_Tab
    0x01000003,      VK_BACK,     // Qt::Key_Backspace
    0x01000004,      VK_RETURN,   // Qt::Key_Return
    0x01000005,      VK_RETURN,   // Qt::Key_Enter
    0x01000006,      VK_INSERT,   // Qt::Key_Insert
    0x01000007,      VK_DELETE,   // Qt::Key_Delete
    0x01000008,      VK_PAUSE,    // Qt::Key_Pause
    0x01000009,      VK_PRINT,    // Qt::Key_Print
    0x0100000a,      VK_SNAPSHOT, // Qt::Key_SysReq
    0x0100000b,      VK_CLEAR,    // Qt::Key_Clear
    0x01000010,      VK_HOME,     // Qt::Key_Home
    0x01000011,      VK_END,      // Qt::Key_End
    0x01000012,      VK_LEFT,     // Qt::Key_Left
    0x01000013,      VK_UP,       // Qt::Key_Up
    0x01000014,      VK_RIGHT,    // Qt::Key_Right
    0x01000015,      VK_DOWN,     // Qt::Key_Down
    0x01000016,      VK_PRIOR,    // Qt::Key_PageUp
    0x01000017,      VK_NEXT,     // Qt::Key_PageDown
    0x01000024,      VK_CAPITAL,  // Qt::Key_CapsLock
    0x01000025,      VK_NUMLOCK,  // Qt::Key_NumLock
    0x01000026,      VK_SCROLL,   // Qt::Key_ScrollLock
    0x01000030,      VK_F1,       // Qt::Key_F1
    0x01000031,      VK_F2,       // Qt::Key_F2
    0x01000032,      VK_F3,       // Qt::Key_F3
    0x01000033,      VK_F4,       // Qt::Key_F4
    0x01000034,      VK_F5,       // Qt::Key_F5
    0x01000035,      VK_F6,       // Qt::Key_F6
    0x01000036,      VK_F7,       // Qt::Key_F7
    0x01000037,      VK_F8,       // Qt::Key_F8
    0x01000038,      VK_F9,       // Qt::Key_F9
    0x01000039,      VK_F10,      // Qt::Key_F10
    0x0100003a,      VK_F11,      // Qt::Key_F11
    0x0100003b,      VK_F12,      // Qt::Key_F12
    0x0100003c,      VK_F13,      // Qt::Key_F13
    0x0100003d,      VK_F14,      // Qt::Key_F14
    0x0100003e,      VK_F15,      // Qt::Key_F15
    0x0100003f,      VK_F16,      // Qt::Key_F16
    0x01000040,      VK_F17,      // Qt::Key_F17
    0x01000041,      VK_F18,      // Qt::Key_F18
    0x01000042,      VK_F19,      // Qt::Key_F19
    0x01000043,      VK_F20,      // Qt::Key_F20
    0x01000044,      VK_F21,      // Qt::Key_F21
    0x01000045,      VK_F22,      // Qt::Key_F22
    0x01000046,      VK_F23,      // Qt::Key_F23
    0x01000047,      VK_F24,      // Qt::Key_F24
    0x01000055,      VK_RMENU,    // Qt::Key_Menu
    0x01000058,      VK_HELP,     // Qt::Key_Help
    0x20      ,      VK_SPACE,    // Qt::Key_Space
    0x30      ,      0x30,        // Qt::Key_0
    0x31      ,      0x31,        // Qt::Key_1
    0x32      ,      0x32,        // Qt::Key_2
    0x33      ,      0x33,        // Qt::Key_3
    0x34      ,      0x34,        // Qt::Key_4
    0x35      ,      0x35,        // Qt::Key_5
    0x36      ,      0x36,        // Qt::Key_6
    0x37      ,      0x37,        // Qt::Key_7
    0x38      ,      0x38,        // Qt::Key_8
    0x39      ,      0x39,        // Qt::Key_9
    0x41      ,      0x41,        // Qt::Key_A
    0x42      ,      0x42,        // Qt::Key_B
    0x43      ,      0x43,        // Qt::Key_C
    0x44      ,      0x44,        // Qt::Key_D
    0x45      ,      0x45,        // Qt::Key_E
    0x46      ,      0x46,        // Qt::Key_F
    0x47      ,      0x47,        // Qt::Key_G
    0x48      ,      0x48,        // Qt::Key_H
    0x49      ,      0x49,        // Qt::Key_I
    0x4a      ,      0x4A,        // Qt::Key_J
    0x4b      ,      0x4B,        // Qt::Key_K
    0x4c      ,      0x4C,        // Qt::Key_L
    0x4d      ,      0x4D,        // Qt::Key_M
    0x4e      ,      0x4E,        // Qt::Key_N
    0x4f      ,      0x4F,        // Qt::Key_O
    0x50      ,      0x50,        // Qt::Key_P
    0x51      ,      0x51,        // Qt::Key_Q
    0x52      ,      0x52,        // Qt::Key_R
    0x53      ,      0x53,        // Qt::Key_S
    0x54      ,      0x54,        // Qt::Key_T
    0x55      ,      0x55,        // Qt::Key_U
    0x5a      ,      0x5A,        // Qt::Key_Z
    0x56      ,      0x56,        // Qt::Key_V
    0x57      ,      0x57,        // Qt::Key_W
    0x58      ,      0x58,        // Qt::Key_X
    0x59      ,      0x59,        // Qt::Key_Y
    Qt::Key_unknown, 0x00         // Qt::Key_unknown. Mark the end of the table
};
