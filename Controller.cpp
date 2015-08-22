#include "Global.hpp"
#include "Controller.hpp"
#include "MainWindow.hpp"
#include "UiEditGameName.hpp"
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

/**
 * @brief Pointer of the singleton
 */
static Controller* controller = nullptr;

/**
 * @brief Private constructor of the singleton
 */
Controller::Controller()
    : QObject(nullptr)
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
 * @brief This method is called by the main window when the application wants to terminate
 * @return bool True if all the game were closed (the application may exit), else false (can't exit)
 */
bool Controller::appCloseRequested()
{
    while (GameList.size() != 0) {
        if (!closeGame(GameList.last().first)) {
            return false; // Game closing aborted by the user
        }
    }
    return true; // All games closed succesfully
}

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
        game->populateUi();                               // Now the game can fill the ui
    }
}

void Controller::openGame()
{
    QString filename = QFileDialog::getOpenFileName(MainWindow::get(), tr("Open a game"), QDir::homePath(), FMETRO_GAME_FILE_FILTER);
    if (!filename.isEmpty()) {
        Game* game = Game::open(filename);
        GameUi* ui = new GameUi;
        MainWindow::get()->addGameUi(ui, game->name());
        GameList.append(QPair<Game*, GameUi*>(game, ui));
        game->populateUi();
    }
}

/**
 * @brief Save a game which has already a filename
 *
 * This method is called by a user request in the main window
 *
 * @param ui Ui of the game to save
 */
void Controller::saveGame(QWidget* ui)
{
    saveGame(gameOf(static_cast<GameUi*>(ui)));
}

/**
 * @brief Save a game which has already a filename
 *
 * @param game Game to save
 */
void Controller::saveGame(Game* game)
{
    game->save();
}

/**
 * @brief Request a filename to save a game to a file
 *
 * This method is called by a user request in the main window
 *
 * @param ui Ui of the game to save
 */
void Controller::saveGameAs(QWidget* ui)
{
    saveGameAs(gameOf(static_cast<GameUi*>(ui)));
}

/**
 * @brief Request a filename to save a game, then save it
 *
 * The game isn't be saved if the file dialog is cancelled
 *
 * @param game The game to save
 * @return bool True if a filename was choosen, else false
 */
bool Controller::saveGameAs(Game* game)
{
    QString filename = QFileDialog::getSaveFileName(MainWindow::get(), QString(tr("Save game %1")).arg(game->name()), QDir::homePath(), FMETRO_GAME_FILE_FILTER);
    if (filename.isEmpty()) {
        return false;
    }
    if (QFileInfo(filename).suffix() != QString(FMETRO_GAME_FILE_EXTENSION)) {
        filename.append(QString(".%1").arg(FMETRO_GAME_FILE_EXTENSION));
    }
    game->setFilename(filename);
    saveGame(game);
    return true;
}

/**
 * @brief Browse all the games, save the ones which have a file, and prompt for the ones which have been newly created
 * @return void
 */
void Controller::saveAllGames()
{
    for (int i = 0; i < GameList.size(); i++) {
        Game* game = GameList[i].first;
        if (game->fullfilename().size() == 0) {
            saveGameAs(game);
        } else {
            saveGame(game);
        }
    }
}

/**
 * @brief Message thrown by the main window to say that the current displayed game is changing
 *
 * @param ui Ui of the new current game
 */
void Controller::newCurrentUi(QWidget* ui)
{
    GameUi* gameui = static_cast<GameUi*>(ui);
    for (int i = 0; i < GameList.size(); i++) {
        if (GameList.at(i).second == gameui) {
            // Change mainwindow title
            // Adjust actions
            break;
        }
    }
}

/**
 * @brief Message thrown by the main window to say that a game needs to be closed
 *
 * @param ui Ui of the game
 */
void Controller::gameCloseRequested(QWidget* ui)
{
    closeGame(gameOf(static_cast<GameUi*>(ui)));
}

/**
 * @brief Method called internally by the controller
 *
 * First, a dialog is popped to ask the user if he wants to save the game
 * If he wants to do so, the game is saved in its file.
 * If the game hasn't a file yet, the user is prompted for a filename. If the user cancels this dialog, the game isn't closed
 *
 * @param game Game to close
 * @return bool True if the game was closed, else false if the user wants to stop the closing process
 */
bool Controller::closeGame(Game* game)
{
    QMessageBox::StandardButton answer;
    if (game->modified()) {
        // The game is modified, but wasn't opened from a file: probably want to "save as"
        if (game->fullfilename().isEmpty()) {
            answer = QMessageBox::question(MainWindow::get(), QString(tr("Close %1")).arg(game->name()), tr("The game %1 is modified, do you want to save it before closing?").arg(game->name()),
                                           QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel);
            if (answer == QMessageBox::StandardButton::Cancel) {
                return false;
            }
            if (answer == QMessageBox::StandardButton::Save) {
                if (!saveGameAs(game)) {
                    return false; // Cancel
                }
            }
        } else {
            // The game is modified, and was opened from a file: probably just need to "save"
            answer = QMessageBox::question(MainWindow::get(), QString(tr("Close %1")).arg(game->name()),
                                           tr("The game %1 (%2) is modified, do you want to save it before closing?").arg(game->name()).arg(game->fullfilename()),
                                           QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel);
            if (answer == QMessageBox::StandardButton::Cancel) {
                return false;
            }
            if (answer == QMessageBox::StandardButton::Save) {
                saveGame(game);
            }
        }
    }

    // Ok, modifications saved or discarded, destroy the game and its ui
    GameUi* ui = uiOf(game);
    MainWindow::get()->RemoveGameUi(ui);
    delete ui;
    delete game;
    GameList.removeOne(QPair<Game*, GameUi*>(game, ui));
    return true;
}

/**
 * @brief Find the game associated with the provided Ui
 * @param ui Ui of the game
 * @return Game* Game associated with the Ui
 */
Game* Controller::gameOf(GameUi* ui)
{
    int i = 0;
    while (GameList.at(i).second != ui) {
        ++i;
    }
    return GameList[i].first;
}

/**
 * @brief Find the ui associated with the provided Game
 * @param game Game of the Ui
 * @return GameUi* Ui associated with the game
 */
GameUi* Controller::uiOf(Game* game)
{
    int i = 0;
    while (GameList.at(i).first != game) {
        ++i;
    }
    return GameList[i].second;
}
