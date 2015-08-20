#include "Controller.hpp"
#include "UiEditGameName.hpp"
#include <QDebug>

/**
 * @brief Pointer of the singleton
 */
static Controller* controller = nullptr;

/**
 * @brief Private constructor of the singleton
 */
Controller::Controller()
    : QObject(nullptr)
    , CurrentGame(nullptr)
{
}

/**
 * @brief Destructor of the singleton. Reset the static pointer
 *
 * The opened games should have been already closed because the QCloseEvent is catched,
 * so the GameList should be already empty, but...
 */
Controller::~Controller()
{
    while (!GameList.isEmpty()) {
        QPair<Game*, GameUi*> pair = GameList.takeLast();
        delete pair.first;
        delete pair.second;
    }
    controller = nullptr; // Should be useless
}

/**
 * @brief Getter of the singleton. Create it if needed
 *
 * @return Controller* Points to the singleton
 */
Controller* Controller::get()
{
    if (controller == nullptr) {
        controller = new Controller;
    }
    return controller;
}

/**
 * @brief Return the instance of the singleton
 *
 * This method returns a pointer which can be used by delete.
 * It won't create an instance if the singleton doesn't exist, but delete supports nullptr
 *
 * @return Controller* Pointer to the singleton if it exists, else nullptr
 */
Controller* Controller::realInstance()
{
    return controller;
}

/***********************************************************
 *
 *          Slots connected from the main window
 *
 ***********************************************************/

/**
 * @brief Create a new game
 *
 * A game needs a name. To avoid a useless creation/destruction if the name input is cancelled,
 * this method prompts for a name, then send it to the game when created
 *
 * @return void
 */
void Controller::newGame()
{
    QString name = UiEditGameName::newGameName();
    if (name.isEmpty()) {
        return;
    }

    GameList.append(QPair<Game*, GameUi*>(new Game, new GameUi));
    CurrentGame = &GameList.last();
    CurrentGame->first->UiReady();
    CurrentGame->first->setName(name);
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


