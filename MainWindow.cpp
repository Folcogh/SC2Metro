#include "MainWindow.hpp"
#include <QList>
#include <QIcon>
#include <QSize>
#include <QToolBar>

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
    addToolBar(toolBar);
}

MainWindow::MainWindow(QString arg)
{
    (void) arg;
}

MainWindow::~MainWindow()
{

}
