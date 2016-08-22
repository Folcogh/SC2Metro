//  SC2 Metronome, a tool for improving mechanics in StarCraft(R) II
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
#include "Modified.hpp"
#include "Timer.hpp"
#include <QMenu>
#include <QAction>
#include <QCloseEvent>
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

// This column is used as the metadata storage because its content is never deleted (neither modified)
#define DATA_COLUMN COLUMN_NAME

// Requested by QTableWidget to store metadata in a QTableWidgetItem
#define TIMER_PTR Qt::UserRole

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWindow)

  public:
    ~MainWindow();
    static MainWindow* instance();                                                // MainWindow is a singleton
    void setTimerStatus(Timer* timer, int status);                                // Called by the timer to update their status in the list
    NativeEventFilter* getNativeEventFilter() const { return nativeEventFilter; } // Allow the timers to connect the NativeEventFilter signal
    void openFile(QString filename);                                              // Used when a file is opened in the CLI (eg. double-clicking an icon)

  private:
    // MainWindow is a singleton
    MainWindow();
    static MainWindow* mainWindow;

    // System related methods
    QMenu* createPopupMenu() override { return nullptr; } // Prevent to close the toolbar by right-clicking it
    void closeEvent(QCloseEvent* event) override;         // Intercept the QCloseEvent to prevent the program to prompt the user for saving if needed
    void updateUI();                                      // Update the main window title and the status of some actions

    // Convenient methods to access a timer
    Timer* getCurrentTimer() const { return timerTable->selectedItems().at(DATA_COLUMN)->data(TIMER_PTR).value<Timer*>(); }
    Timer* getTimer(int row) const { return timerTable->item(row, DATA_COLUMN)->data(TIMER_PTR).value<Timer*>(); }
    int getCurrentRow() const { return timerTable->selectedItems().at(0)->row(); }
    //
    // Actions triggerred by the icons of the main toolbar
    QAction* actionNewList;
    QAction* actionOpenList;
    QAction* actionSaveList;
    QAction* actionNewTimer;
    QAction* actionEditTimer;
    QAction* actionRemoveTimer;
    QAction* actionMisc;

    // Methods triggered by the actions
    void newListTriggerred();
    void openListTriggerred();
    void newTimerTriggerred();
    void editTimerTriggerred();
    void removeTimerTriggerred();

    // Timers
    QTableWidget* timerTable;
    void addTimerToTable(Timer* timer); // Used when the user create a timer or when a file is opened
    void deleteAllTimers();             // Delete the Timer associated with each row of the table. Used by the dtor, or when the list is cleared
    void clearList();                   // Delete the Timers, then remove the entries of the list
    void timerSelectionChanged();       // used to unable/disable actionEditTimer/actionRemoveTimer

    // Hotkey handling
    NativeEventFilter* nativeEventFilter; // Handler receiving the Windows events
    int hotkeyID;                         // Counter making each hotkey unique for the System

    // File handling
    Modified modified;        // Emit a signal on change
    QString currentFilename;  // Name of the file currently opened. Empty if the list doesn't belong to a file
    QString previousPath;     // Last valid path used by the Open/Save dialogs
    bool promptForSaving();   // If the current list is modified, ask the user if he wants to save it
    bool promptForFilename(); // If the current filename is empty, ask the user where he wants to save the current list
    bool save();              // Save the current list in the current filename
};

#endif // MAINWINDOW_HPP
