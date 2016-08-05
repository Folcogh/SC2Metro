//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

//  You should have received a copy of the GNU General Public License along with this program.
//  If not, see <http://www.gnu.org/licenses/>.

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "NativeEventFilter.hpp"
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QKeySequence>
#include <QTableWidget>

// Size of the icons in the main toolbar
#define MAIN_TOOLBAR_ICON_WIDTH 64
#define MAIN_TOOLBAR_ICON_HEIGHT 64

// Index of the columns in the timers table
#define COLUMN_STATUS 0
#define COLUMN_NAME 1
#define COLUMN_PERIOD 2
#define COLUMN_HOTKEY 3
#define COLUMN_COUNT 4

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    ~MainWindow();
    static MainWindow* instance();
    void establishExternalConnections();

    // Methods called by the TimerList instance
    void newTimer(QString filename, int period, QKeySequence keySequence);
    void editTimer(int row, int period, QKeySequence keySequence);
    void removeTimer(int row);
    void setTimerPlaying(int index);
    void setTimerStopped(int index);

  private:
    Q_DISABLE_COPY(MainWindow)

    // MainWindow is a singleton
    static MainWindow* mainWindow;
    MainWindow();

    // Native event filter (for the hotkeys)
    NativeEventFilter* nativeEventFilter;

    // These actions are icons in the main toolbar
    QAction* actionNewList;
    QAction* actionOpenList;
    QAction* actionSaveList;
    QAction* actionNewTimer;
    QAction* actionEditTimer;
    QAction* actionRemoveTimer;
    QAction* actionMisc;

    // Prevent the toolbar to be hidden with a context menu
    QMenu* createPopupMenu() override;

    // Main widget, displaying the timers
    QTableWidget* timerTable;

    // Methods called when the actions in the toolbar are triggerred*
    void newTimerTriggerred();
    void editTimerTriggerred();
    void removeTimerTriggerred();

    // Methods triggered by the table signals
    void timerSelectionChanged();
};

#endif // MAINWINDOW_HPP
