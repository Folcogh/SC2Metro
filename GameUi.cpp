#include "GameUi.hpp"
#include "Controller.hpp"
#include "CyclicTimerViewData.hpp"
#include <QGroupBox>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

GameUi::GameUi()
    : QWidget(nullptr)
{
    /***********************************************************
     *
     *          Cyclic timers interface
     *
     ***********************************************************/

    // Buttons
    ButtonAddCyclic = new QPushButton(tr("Add a new timer"));
    ButtonEditCyclic = new QPushButton(tr("Edit this timer"));
    ButtonRemoveCyclic = new QPushButton(tr("Remove this timer"));
    QHBoxLayout* CyclicButtonsLayout = new QHBoxLayout;
    CyclicButtonsLayout->addWidget(ButtonAddCyclic);
    CyclicButtonsLayout->addWidget(ButtonEditCyclic);
    CyclicButtonsLayout->addWidget(ButtonRemoveCyclic);

    // Main layout
    QVBoxLayout* CyclicLayout = new QVBoxLayout;
    CyclicTable = new QTableWidget(0, 7);
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
    CyclicTable->setAlternatingRowColors(true);
    CyclicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    CyclicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    CyclicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CyclicTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    CyclicTable->setDragEnabled(false);
    CyclicTable->setSortingEnabled(true);
    CyclicTable->setTabKeyNavigation(false);
    CyclicTable->setShowGrid(false);

    // Buttons configuration
    ButtonEditCyclic->setEnabled(false);
    ButtonRemoveCyclic->setEnabled(false);

    // Connections
    connect(ButtonAddCyclic, &QPushButton::clicked, this, &GameUi::newCyclicTimer);

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
void GameUi::newCyclicTimer()
{
    CYCLIC_TIMER_VIEW_DATA* data = new CYCLIC_TIMER_VIEW_DATA;
    if (!Controller::get()->newCyclicTimer(this, data)) {
        delete data;
        return;
    }
}
