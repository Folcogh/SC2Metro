#include "MainWindow.hpp"
#include "TimerList.hpp"
#include <QList>
#include <QIcon>
#include <QSize>
#include <QToolBar>
#include <QStringList>
#include <QHeaderView>
#include <QAbstractItemView>

MainWindow* MainWindow::mainWindow = nullptr;

MainWindow::MainWindow()
{
    /*
     * Create the actions. they will be available in the main toolbar
     *
     */
    QAction* actionNewList = new QAction(QIcon(":/icon64/NewList.png"), "", this);
    actionNewList->setToolTip(tr("Create a new empty list"));

    QAction* actionOpenList = new QAction(QIcon(":/icon64/OpenList.png"), "", this);
    actionOpenList->setToolTip(tr("Open an existing list"));

    this->actionSaveList = new QAction(QIcon(":/icon64/SaveList.png"), "", this);
    this->actionSaveList->setToolTip(tr("Save the current list"));

    QAction* actionNewTimer = new QAction(QIcon(":/icon64/NewTimer.png"), "", this);
    actionNewTimer->setToolTip(tr("Create a new Timer for the current list"));

    this->actionEditTimer = new QAction(QIcon(":/icon64/EditTimer.png"), "", this);
    this->actionEditTimer->setToolTip(tr("Modify the currently selected Timer"));

    this->actionRemovTimer = new QAction(QIcon(":/icon64/RemoveTimer.png"), "", this);
    this->actionRemovTimer->setToolTip(tr("Remove the currently selected timer"));

    QAction* actionMisc = new QAction(QIcon(":/icon64/Misc.png"), "", this);
    actionMisc->setToolTip(tr("About, Help and Licenses"));

    QAction* actionSeparator1 = new QAction(this);
    QAction* actionSeparator2 = new QAction(this);
    actionSeparator1->setSeparator(true);
    actionSeparator2->setSeparator(true);

    /*
     * Create the main toolbar and insert the actions
     *
     */
    QList<QAction*> actionList;
    actionList << actionNewList
               << actionOpenList
               << actionSaveList
               << actionSeparator1
               << actionNewTimer
               << actionEditTimer
               << actionRemovTimer
               << actionSeparator2
               << actionMisc;

    QSize iconSize;
    iconSize.setWidth(MAIN_TOOLBAR_ICON_WIDTH);
    iconSize.setHeight(MAIN_TOOLBAR_ICON_HEIGHT);

    QToolBar* toolBar = new QToolBar(this);
    toolBar->setIconSize(iconSize);
    toolBar->addActions(actionList);
    toolBar->setMovable(false);
    this->addToolBar(toolBar);

    /*
     * Create the main widget, a table which display the timers
     * The table display three columns: sound name, period and shortcut
     *
     */
    this->timerTable = new QTableWidget(0, 3, this);

    // Table properties
    this->timerTable->setShowGrid(true);
    this->timerTable->setSortingEnabled(false);
    this->timerTable->setAlternatingRowColors(true);
    this->timerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->timerTable->setSelectionMode(QAbstractItemView::SingleSelection);
    this->timerTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->timerTable->horizontalHeader()->setStretchLastSection(true);

    // Set the columns header
    QStringList labels;
    labels << tr("Sound name")
           << tr("Period")
           << tr("Hotkey");
    this->timerTable->setHorizontalHeaderLabels(labels);

    this->timerTable->setColumnWidth(COLUMN_SOUND, 200);
    this->timerTable->setColumnWidth(COLUMN_PERIOD, 100);
    this->timerTable->setColumnWidth(COLUMN_HOTKEY, 200);

    // Finally, install the table in the main window
    this->setCentralWidget(this->timerTable);


}

MainWindow::~MainWindow()
{
    this->mainWindow = nullptr;
}

MainWindow* MainWindow::instance()
{
    if (mainWindow == nullptr) {
        mainWindow = new MainWindow;
    }
    return mainWindow;
}

QMenu* MainWindow::createPopupMenu()
{
    return nullptr;
}
