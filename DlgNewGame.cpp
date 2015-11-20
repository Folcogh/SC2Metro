#include "DlgNewGame.hpp"
#include "ui_DlgNewGame.h"
#include "MainWindow.hpp"
#include "Race.hpp"
#include <QButtonGroup>

DlgNewGame::DlgNewGame()
    : QDialog(MainWindow::get())
    , ui(new Ui::DlgNewGame)
    , m_Protoss(":/Images/racelogos/Protoss.png")
    , m_ProtossGray(":/Images/racelogos/ProtossGray.png")
    , m_Terran(":/Images/racelogos/Terran.png")
    , m_TerranGray(":/Images/racelogos/TerranGray.png")
    , m_Zerg(":/Images/racelogos/Zerg.png")
    , m_ZergGray(":/Images/racelogos/ZergGray.png")
{
    ui->setupUi(this);
    adjustSize();

    // Connections
    connect(ui->buttonOK, &QPushButton::clicked, this, &DlgNewGame::accept);
    connect(ui->buttonCancel, &QPushButton::clicked, this, &DlgNewGame::reject);
    connect(ui->editName, &QLineEdit::textChanged, this, &DlgNewGame::adjustButtonOk);
    connect(ui->buttonsRace, static_cast<void(QButtonGroup::*)(QAbstractButton*)>(&QButtonGroup::buttonClicked), this, &DlgNewGame::raceClicked); // Funky syntax, see Qt doc
}

DlgNewGame::~DlgNewGame()
{
    delete ui;
}

int DlgNewGame::getRace()
{
    int race;
    QAbstractButton* button = ui->buttonsRace->checkedButton();
    if (button == ui->buttonProtoss) {
        race = RACE_PROTOSS;
    }
    else if (button == ui->buttonTerran) {
        race = RACE_TERRAN;
    }
    else {
        race = RACE_ZERG;
    }
    return race;
}

QString DlgNewGame::getName()
{
    return ui->editName->text();
}

void DlgNewGame::raceClicked(QAbstractButton* button)
{
    ui->buttonProtoss->setIcon(m_ProtossGray);
    ui->buttonTerran->setIcon(m_TerranGray);
    ui->buttonZerg->setIcon(m_ZergGray);
    if (button == ui->buttonProtoss) {
        ui->buttonProtoss->setIcon(m_Protoss);
    }
    else if (button == ui->buttonTerran) {
        ui->buttonTerran->setIcon(m_Terran);
    }
    else {
        ui->buttonZerg->setIcon(m_Zerg);
    }
}

void DlgNewGame::adjustButtonOk()
{
    if (ui->editName->text().isEmpty()) {
        ui->buttonOK->setDisabled(true);
    }
    else {
        ui->buttonOK->setEnabled(true);
    }
}
