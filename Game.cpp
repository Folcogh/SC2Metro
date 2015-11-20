#include "Game.hpp"
#include "ui_Game.h"
#include "MainWindow.hpp"
#include "DlgNewGame.hpp"
#include "CyclicTimer.hpp"
#include "EditGameName.hpp"
#include <QPointer>

Game::Game(QString name, int race)
    : ui(new Ui::Game)
    , m_name(name)
    , m_race(race)
    , m_modified(true)
{
    ui->setupUi(this);
}

Game::~Game()
{
    delete ui;
    deleteLater();
}

void Game::closeEvent(QCloseEvent* event)
{
    event->accept();
    if (m_modified) {
        // save/save as toussa
    }
}

bool Game::isModified()
{
    return m_modified;
}

Game* Game::newGame()
{
    Game* game = nullptr;
    QPointer<DlgNewGame> dlg = new DlgNewGame;
    if (dlg->exec() == QDialog::Accepted) {
        game = new Game(dlg->getName(), dlg->getRace());
    }
    delete dlg;
    return game;
}

void Game::editName()
{
    QString name = EditGameName::editGameName(m_name);
    if (m_name != name) {
        m_name = name;
        m_modified = true;
    }
}
