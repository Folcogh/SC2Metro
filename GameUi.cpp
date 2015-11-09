#include "GameUi.hpp"
#include "Global.hpp"
#include "Controller.hpp"
#include "MainWindow.hpp"
#include "CyclicTimerData.hpp"
#include "CyclicTimerItem.hpp"
#include "ActionPushButton.hpp"
#include <QString>
#include <QVariant>
#include <QGroupBox>
#include <QTableView>
#include <QBoxLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>

Q_DECLARE_METATYPE(CyclicTimerData*)

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
    ButtonEditCyclic = new ActionPushButton(MainWindow::get()->actionEditCyclicTimer());
    ButtonRemoveCyclic = new ActionPushButton(MainWindow::get()->actionRemoveCyclicTimer());
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
    headerLabels << tr("Enabled") << tr("Sound") << tr("Period") << tr("Start") << tr("Terminate") << tr("Hotkey") << tr("Volume");
    CyclicTable->setHorizontalHeaderLabels(headerLabels);
    CyclicTable->verticalHeader()->setVisible(false);
    CyclicTable->horizontalHeader()->setStretchLastSection(true);
    CyclicTable->setSortingEnabled(true);
    CyclicTable->sortByColumn(Column::Sound, Qt::AscendingOrder);
    CyclicTable->setShowGrid(false);
    CyclicTable->setAlternatingRowColors(true);
    CyclicTable->setSelectionMode(QAbstractItemView::SingleSelection);
    CyclicTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    CyclicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CyclicTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    CyclicTable->setDragEnabled(false);
    CyclicTable->setTabKeyNavigation(false);

    // Connections
    connect(CyclicTable, &QTableWidget::itemSelectionChanged, this, &GameUi::cyclicTableSelectionChanged);

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
    // Freeze the table
    CyclicTable->blockSignals(true);
    CyclicTable->setUpdatesEnabled(false);
    CyclicTable->setSortingEnabled(false);

    // Add new item at row 0
    CyclicTable->insertRow(0);

    // Enabled/disabled status
    CyclicTimerItem* enabled = new CyclicTimerItem(tr("yes"));
    enabled->setData(Role::CyclicTimerDataPointer, QVariant::fromValue<CyclicTimerData*>(data));
    enabled->setCheckState(Qt::Checked);
    CyclicTable->setItem(0, Column::EnabledStatus, enabled);

    // Sound file
    CyclicTable->setItem(0, Column::Sound, new CyclicTimerItem(data->sound()));

    // Period
    CyclicTable->setItem(0, Column::Period, new CyclicTimerItem(FORMAT_DURATION_mm_ss(data->period())));

    // Start
    QString strStart("immediately");
    if (data->start() != 0) {
        strStart = FORMAT_DURATION_mm_ss(data->start());
    }
    CyclicTable->setItem(0, Column::Start, new CyclicTimerItem(strStart));

    // Terminate
    QString strTerminate("never");
    if (data->terminate() != 0) {
        strTerminate = FORMAT_DURATION_mm_ss(data->terminate());
    }
    CyclicTable->setItem(0, Column::Terminate, new CyclicTimerItem(strTerminate));

    // Hotkey
    QString strHotkey(data->hotkey().toString());
    if (strHotkey.isEmpty()) {
        strHotkey.append("-");
    }
    CyclicTable->setItem(0, Column::Hotkey, new CyclicTimerItem(strHotkey));

    // Volume
    CyclicTable->setItem(0, Column::Volume, new CyclicTimerItem(QString("%1%").arg(data->volume())));

    // Establish connections
    connect(CyclicTable, &QTableWidget::itemChanged, this, &GameUi::cyclicTimerCheckChanged);

    // Unfreeze the table
    CyclicTable->setSortingEnabled(true);
    CyclicTable->setUpdatesEnabled(true);
    CyclicTable->blockSignals(false);
}

void GameUi::cyclicTableSelectionChanged()
{
    Controller::get()->cyclicTimerSelectionChanged(this);
}

void GameUi::cyclicTimerCheckChanged(QTableWidgetItem* item)
{
    Controller::get()->cyclicTimerCheckChanged(this, item);
}

CyclicTimerData* GameUi::currentCyclicTimerData()
{
    int x = CyclicTable->currentRow();
    int y = Column::EnabledStatus;
    CyclicTimerItem* item = static_cast<CyclicTimerItem*>(CyclicTable->item(x, y));
}
