//  SC2 Metronome, a tool for improving mechanics in StarCraft 2(TM)
//  Copyright (C) 2016 Martial Demolins AKA Folco

//  This program is free software: you can redistribute it and/or modify it
//  under the terms of the GNU General Public License
//  as published by the Free Software foundation, either version 3 of the
//  License, or (at your option) any later version.

//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty
//  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//  Public License for more details.

//  You should have received a copy of the GNU General Public License along with
//  this program.
//  If not, see <http://www.gnu.org/licenses/>.

#include "NativeEventFilter.hpp"
#include "DlgEditTimer.hpp"
#include "DlgNewTimer.hpp"
#include "SMException.hpp"
#include "MainWindow.hpp"
#include "TableItem.hpp"
#include <QSize>
#include <QChar>
#include <QIcon>
#include <QList>
#include <QList>
#include <QToolBar>
#include <QVariant>
#include <QPointer>
#include <QFileInfo>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>
#include <QAbstractItemView>

MainWindow* MainWindow::mainWindow = nullptr;

MainWindow::MainWindow()
    : hotkeyID(0)
{
    // Install a native event filter to handle the hotkeys
    this->nativeEventFilter = new NativeEventFilter;

    // Create the actions. they will be available in the main toolbar
    this->actionNewList = new QAction(QIcon(":/icon64/NewList.png"), "", this);
    this->actionNewList->setToolTip(tr("Create a new empty list"));

    this->actionOpenList = new QAction(QIcon(":/icon64/OpenList.png"), "", this);
    this->actionOpenList->setToolTip(tr("Open an existing list"));

    this->actionSaveList = new QAction(QIcon(":/icon64/SaveList.png"), "", this);
    this->actionSaveList->setToolTip(tr("Save the current list"));

    this->actionNewTimer = new QAction(QIcon(":/icon64/NewTimer.png"), "", this);
    this->actionNewTimer->setToolTip(tr("Create a new Timer for the current list"));

    this->actionEditTimer = new QAction(QIcon(":/icon64/EditTimer.png"), "", this);
    this->actionEditTimer->setToolTip(tr("Modify the currently selected Timer"));

    this->actionRemoveTimer = new QAction(QIcon(":/icon64/RemoveTimer.png"), "", this);
    this->actionRemoveTimer->setToolTip(tr("Remove the currently selected timer"));

    this->actionMisc = new QAction(QIcon(":/icon64/Misc.png"), "", this);
    this->actionMisc->setToolTip(tr("About, Help and Licenses"));

    QAction* actionSeparator1 = new QAction(this);
    QAction* actionSeparator2 = new QAction(this);
    actionSeparator1->setSeparator(true);
    actionSeparator2->setSeparator(true);

    // Create the main toolbar and insert the actions
    QList<QAction*> actionList;
    actionList << actionNewList << actionOpenList << actionSaveList << actionSeparator1 << actionNewTimer << actionEditTimer << actionRemoveTimer
               << actionSeparator2 << actionMisc;

    QSize iconSize(MAIN_TOOLBAR_ICON_WIDTH, MAIN_TOOLBAR_ICON_HEIGHT);

    QToolBar* toolBar = new QToolBar(this);
    toolBar->setIconSize(iconSize);
    toolBar->addActions(actionList);
    toolBar->setMovable(false);
    this->addToolBar(toolBar);

    // Create the main widget, a table which display the timers
    // The table display three columns: sound name, period and hotkey
    this->timerTable = new QTableWidget(0, COLUMN_COUNT, this);

    // Table properties
    this->timerTable->setShowGrid(true);
    this->timerTable->setSortingEnabled(false);
    this->timerTable->setAlternatingRowColors(true);
    this->timerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->timerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    this->timerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->timerTable->horizontalHeader()->setStretchLastSection(true);
    this->timerTable->verticalHeader()->setVisible(false);

    // Set the columns header and size
    QStringList labels;
    labels << tr("Status") << tr("Sound name") << tr("Period") << tr("Hotkey");
    this->timerTable->setHorizontalHeaderLabels(labels);

    this->timerTable->setColumnWidth(COLUMN_STATUS, 60);
    this->timerTable->setColumnWidth(COLUMN_NAME, 200);
    this->timerTable->setColumnWidth(COLUMN_PERIOD, 100);
    this->timerTable->setColumnWidth(COLUMN_HOTKEY, 200);

    // Finally, install the table in the main window
    setCentralWidget(this->timerTable);

    // Main toolbar connections
    connect(this->actionNewTimer, &QAction::triggered, this, &MainWindow::newTimerTriggerred);
    connect(this->actionEditTimer, &QAction::triggered, this, &MainWindow::editTimerTriggerred);
    connect(this->actionRemoveTimer, &QAction::triggered, this, &MainWindow::removeTimerTriggerred);

    // Table connections
    connect(this->timerTable, &QTableWidget::itemSelectionChanged, this, &MainWindow::timerSelectionChanged);
    connect(this->timerTable, &QTableWidget::itemDoubleClicked, this, &MainWindow::editTimerTriggerred);

    // Trigger some slots to have a consistent interface
    timerSelectionChanged();
}

MainWindow::~MainWindow()
{
    // First, delete the event filter to disable all the hotkeys at once
    delete this->nativeEventFilter;

    // Remove all the timers
    for (int row = 0; row < this->timerTable->rowCount(); row++) {
        Timer* timer = getTimer(row);
        delete timer;
    }

    // Safety: set the singleton ptr to null
    this->mainWindow = nullptr;
}

// MainWindow is a singleton
MainWindow* MainWindow::instance()
{
    if (mainWindow == nullptr) {
        mainWindow = new MainWindow;
    }
    return mainWindow;
}

// Return the timer currently selected
Timer* MainWindow::getCurrentTimer()
{
    QList<QTableWidgetItem*> selection = this->timerTable->selectedItems();
    QTableWidgetItem* item             = selection.at(DATA_COLUMN);
    QVariant data                      = item->data(TIMER_PTR);
    return data.value<Timer*>();
}

// Return the timer of a row
Timer* MainWindow::getTimer(int row)
{
    QTableWidgetItem* item = this->timerTable->item(row, DATA_COLUMN);
    QVariant data          = item->data(TIMER_PTR);
    Timer* timer           = data.value<Timer*>();
    return timer;
}

// Return the current row
int MainWindow::getCurrentRow()
{
    QList<QTableWidgetItem*> selectedItems = this->timerTable->selectedItems();
    return selectedItems.at(0)->row();
}

// Prevent a menu to pop up when right clicking the toolbar, which would allow to hide it
QMenu* MainWindow::createPopupMenu()
{
    return nullptr;
}

//
//  Methods called when the toolbar actions are triggered
//

void MainWindow::newTimerTriggerred()
{
    QPointer<DlgNewTimer> dlg = new DlgNewTimer(this);
    if (dlg->exec() == QDialog::Accepted) {
        Timer* timer;
        try {
            timer =
                new Timer(dlg->getFilename(), dlg->getPeriod(), dlg->getKeySquence(), dlg->getNativeVirtualKey(), dlg->getNativeModifiers(), this->hotkeyID);
            this->hotkeyID++;
        }
        catch (const SMException& exception) {
            QString message = QString(tr("Couldn't create the timer: %1")).arg(exception.getMessage());
            QMessageBox::critical(this, "Error", message, QMessageBox::Ok);
            return;
        }

        TableItem* itemStatus = new TableItem(QString());

        QString filename      = timer->getFilename();
        QString displayedName = QFileInfo(filename).completeBaseName();
        TableItem* itemName   = new TableItem(displayedName);

        int period              = timer->getPeriod();
        QString displayedPeriod = QString("%1:%2").arg(period / 60, 2, 10, QChar('0')).arg(period % 60, 2, 10, QChar('0'));
        TableItem* itemPeriod   = new TableItem(displayedPeriod);

        QKeySequence keySequence = timer->getKeySequence();
        QString displayedHotkey  = keySequence.toString();
        TableItem* itemHotkey    = new TableItem(displayedHotkey);

        int row = this->timerTable->rowCount();
        this->timerTable->insertRow(row);
        this->timerTable->setItem(row, COLUMN_STATUS, itemStatus);
        this->timerTable->setItem(row, COLUMN_NAME, itemName);
        this->timerTable->setItem(row, COLUMN_PERIOD, itemPeriod);
        this->timerTable->setItem(row, COLUMN_HOTKEY, itemHotkey);

        QVariant data = QVariant::fromValue<Timer*>(timer);
        this->timerTable->item(row, DATA_COLUMN)->setData(TIMER_PTR, data);

        setTimerStatus(timer, STATUS_STOPPED);
    }
    delete dlg;
}

void MainWindow::editTimerTriggerred()
{
    Timer* timer = getCurrentTimer();

    // Prevent the user to edit the timer if its media is broken
    if (timer->isBroken()) {
        QMessageBox::warning(this, tr("Error"), tr("This timer can't be modified because it's broken"), QMessageBox::Ok);
    }
    else {
        QString filename         = timer->getFilename();
        int period               = timer->getPeriod();
        QKeySequence keySequence = timer->getKeySequence();
        UINT virtualKey          = timer->getVirtualKey();
        UINT modifiers           = timer->getModifiers();

        QPointer<DlgEditTimer> dlg = new DlgEditTimer(filename, period, keySequence, virtualKey, modifiers, this);
        if (dlg->exec() == QDialog::Accepted) {
            try {
                timer->setNewData(dlg->getPeriod(), dlg->getKeySquence(), dlg->getNativeVirtualKey(), dlg->getNativeModifiers(), this->hotkeyID);
                this->hotkeyID++;
            }
            catch (const SMException& exception) {
                QString message = QString(tr("Couldn't modify the timer: %1")).arg(exception.getMessage());
                QMessageBox::critical(this, "Error", message, QMessageBox::Ok);
                return;
            }

            int period              = timer->getPeriod();
            QString displayedPeriod = QString("%1:%2").arg(period / 60, 2, 10, QChar('0')).arg(period % 60, 2, 10, QChar('0'));
            TableItem* itemPeriod   = new TableItem(displayedPeriod);

            QKeySequence keySequence = timer->getKeySequence();
            QString displayedHotkey  = keySequence.toString();
            TableItem* itemHotkey    = new TableItem(displayedHotkey);

            int row = getCurrentRow();
            this->timerTable->setItem(row, COLUMN_PERIOD, itemPeriod);
            this->timerTable->setItem(row, COLUMN_HOTKEY, itemHotkey);
        }
        delete dlg;
    }
}

void MainWindow::removeTimerTriggerred()
{
    int rowToRemove = getCurrentRow();
    Timer* timer                           = getCurrentTimer();

    delete timer;
    this->timerTable->removeRow(rowToRemove);
}

// Called by the native event filter when a global hotkey is received
bool MainWindow::hotkeyReceived(unsigned int id)
{
    for (int row = 0; row < this->timerTable->rowCount(); row++) {
        Timer* timer = getTimer(row);
        if (timer->getHotkeyId() == id) {
            if (!timer->isBroken()) {
                timer->togglePlayStop();
            }
            return true;
        }
    }
    return false;
}

// Slot called when the selection changes in the table
void MainWindow::timerSelectionChanged()
{
    QList<QTableWidgetItem*> selectedItems = this->timerTable->selectedItems();
    if (selectedItems.isEmpty()) {
        this->actionEditTimer->setDisabled(true);
        this->actionRemoveTimer->setDisabled(true);
    }
    else {
        this->actionEditTimer->setEnabled(true);
        this->actionRemoveTimer->setEnabled(true);
    }
}

// Called by the timers when their status change
void MainWindow::setTimerStatus(Timer* timer, int status)
{
    for (int row = 0; row < this->timerTable->rowCount(); row++) {
        Timer* candidateTimer = getTimer(row);
        if (timer == candidateTimer) {
            QString displayedStatus;
            switch (status) {
                case STATUS_STOPPED:
                    displayedStatus = tr("stopped");
                    break;
                case STATUS_PLAYING:
                    displayedStatus = tr("playing");
                    break;
                case STATUS_BROKEN:
                    displayedStatus = tr("broken");
                    break;
                default:
                    displayedStatus = tr("<undefined>");
            }
            this->timerTable->item(row, COLUMN_STATUS)->setText(displayedStatus);
        }
    }
}
