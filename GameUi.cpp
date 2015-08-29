#include "GameUi.hpp"
#include "Controller.hpp"
#include "MainWindow.hpp"
#include "CyclicTimerData.hpp"
#include "ActionPushButton.hpp"
#include <QGroupBox>
#include <QTableView>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>

GameUi::GameUi()
    : QWidget(nullptr)
{
    /***********************************************************
     *
     *          Cyclic timers interface
     *
     ***********************************************************/

    // Buttons
    ButtonAddCyclic = new ActionPushButton(MainWindow::get()->actionNewCyclicTimer());
    ButtonEditCyclic = new QPushButton(tr("Edit this timer"));
    ButtonRemoveCyclic = new QPushButton(tr("Remove this timer"));
    QHBoxLayout* CyclicButtonsLayout = new QHBoxLayout;
    CyclicButtonsLayout->addWidget(ButtonAddCyclic);
    CyclicButtonsLayout->addWidget(ButtonEditCyclic);
    CyclicButtonsLayout->addWidget(ButtonRemoveCyclic);

    // Main layout
    CyclicTable = new QTableWidget(0, 7);
    QVBoxLayout* CyclicLayout = new QVBoxLayout;
    CyclicLayout->addWidget(CyclicTable);
    CyclicLayout->addLayout(CyclicButtonsLayout);

    // Box
    QGroupBox* CyclicBox = new QGroupBox(tr("Cyclic timers"));
    CyclicBox->setLayout(CyclicLayout);

    // Table configuration
    QStringList headerLabels;
    headerLabels << tr("Enabled") << tr("Sound") << tr("Period") << tr("Start at") << tr("Terminate at") << tr("Hotkey") << tr("Volume");
    CyclicTable->setHorizontalHeaderLabels(headerLabels);
    CyclicTable->verticalHeader()->setVisible(false);
    CyclicTable->horizontalHeader()->setStretchLastSection(true);
    CyclicTable->setSortingEnabled(true);
    CyclicTable->setShowGrid(false);
    CyclicTable->setAlternatingRowColors(true);
    CyclicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    CyclicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    CyclicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CyclicTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    CyclicTable->setDragEnabled(false);
    CyclicTable->setTabKeyNavigation(false);

    // Buttons configuration
    ButtonEditCyclic->setEnabled(false);
    ButtonRemoveCyclic->setEnabled(false);

    /***********************************************************
     *
     *          Game ui
     *
     ***********************************************************/

    setLayout(new QVBoxLayout);
    layout()->addWidget(CyclicBox);
}

GameUi::~GameUi()
{
}

/**
 * @brief Add a cyclic timer in the list
 * @return void
 */
void GameUi::newCyclicTimer(CyclicTimerData* data)
{
    CyclicTable->blockSignals(true);
    CyclicTable->setUpdatesEnabled(false);
    CyclicTable->setSortingEnabled(false);

    // Add new item

    CyclicTable->setSortingEnabled(true);
    CyclicTable->setUpdatesEnabled(true);
    CyclicTable->blockSignals(false);
}
