#include "Controller.hpp"
#include <QDebug>

// Pointer of the singleton
static Controller* controller = nullptr;

Controller::Controller()
    : QObject(nullptr)
    , CurrentGame(nullptr)
{
    if (controller != nullptr) {
        qDebug() << "Controller already created";
        abort();
    }
    controller = this;
}

Controller::~Controller()
{
    while (!GameList.isEmpty()) {
        QPair<Game*, GameUi*> pair = GameList.takeLast();
        delete pair.first;
        delete pair.second;
    }
    controller = nullptr; // Should be useless
}

Controller* Controller::get()
{
    return controller;
}

// Slots connected from the main window
void Controller::newGame()
{
    GameList.append(QPair<Game*, GameUi*>(new Game, new GameUi));
}

void Controller::openGame()
{

}

void Controller::saveGame()
{

}

void Controller::saveGameAs()
{

}

void Controller::saveAllGames()
{

}

void Controller::closeCurrentGame()
{

}
