#include "Controller.hpp"
#include "MainWindow.hpp"
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
 * this method prompts for a name, then sends it to the game when created
 *
 * @return void
 */
void Controller::newGame()
{
    QString name = UiEditGameName::newGameName();
    if (!name.isEmpty()) {
        Game* game = new Game(name);                      // Create the game
        GameUi* ui = new GameUi;                          // Create the ui
        MainWindow::get()->addGameUi(ui, name);           // Add it to the main window
        GameList.append(QPair<Game*, GameUi*>(game, ui)); // Push the game/ui pair
        CurrentGame = &GameList.last();                   // Update CurrentGame
        game->populateUi();                               // Now the game can fill the ui
    }
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
    if (CurrentGame->first->modified()) {
        // ask if save
    }
}

void Controller::newCurrentUi(QWidget* ui)
{
    GameUi* gameui = static_cast<GameUi*>(ui);
    for (int i = 0; i < GameList.size(); i ++) {
        if (GameList.at(i).second == gameui) {
            CurrentGame = &GameList[i];
            break;
        }
    }
}

void Controller::gameCloseRequested(QWidget* ui)
{
    GameUi* gameui = static_cast<GameUi*>(ui);
    if (gameOf(gameui)->modified()) {
        // ask if save
    }
}

Game* Controller::gameOf(GameUi* ui)
{
    for (int i = 0; i < GameList.size(); i ++) {
        if (GameList.at(i).second == ui) {
            return GameList.at(i).first;
        }
    }
    return nullptr;
}
