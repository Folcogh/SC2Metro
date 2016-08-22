//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

// This file contains application-wide constants

#ifndef SC2METRO_HPP
#define SC2METRO_HPP

#define LIST_FILTER "*.sml"        // Filter to open/save a timer list
#define SOUND_FILTER "*.mp3 *.wav" // Supported sound format
#define BUILTIN_TAG " (builtin)"   // Added in the DlgEditTimer dialog to the builtin sound names

#define VERSION 2                         // Version of the program
#define SHORT_NAME "SC2Metro"             //
#define MAINWINDOW_TITLE "SC2 Metronome"  // The name displayed in the menu bar
#define APPLICATION_NAME MAINWINDOW_TITLE // Used for QApplication

#endif // SC2METRO_HPP
