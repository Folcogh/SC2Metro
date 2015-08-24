#include "Global.hpp"
#include "Controller.hpp"
#include "MainWindow.hpp"
#include "UiEditGameName.hpp"
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>

/***********************************************************
 *
 *          Singleton stuff
 *
 ***********************************************************/

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
 *          Internal methods
 *
 ***********************************************************/

/**
 * @brief Find the game associated with the provided Ui
 *
 * Due to MainWindow throwing newCurrentUi(index), with index == -1, this method supports ui == nullptr
 * In this case, it returns Game* == nullptr
 *
 * @param ui Ui of the game
 * @return Game* Game associated with the Ui
 */
Game* Controller::gameOf(GameUi* ui) const
{
    Game* game = nullptr;
    for (int i = 0; i < GameList.size(); i++) {
        if (GameList.at(i).second == ui) {
            game = GameList.at(i).first;
            break;
        }
    }
    return game;
}

/**
 * @brief Find the ui associated with the provided Game
 *
 * Due to MainWindow throwing newCurrentUi(index), with index == -1, this method supports game == nullptr
 * In this case, it returns GameUi* == nullptr
 *
 * @param game Game of the Ui (mays be nullptr)
 * @return GameUi* Ui associated with the game, or nullptr
 */
GameUi* Controller::gameUiOf(Game* game) const
{
    GameUi* ui = nullptr;
    for (int i = 0; i < GameList.size(); i++) {
        if (GameList.at(i).first == game) {
            ui = GameList.at(i).second;
            break;
        }
    }
    return ui;
}

/**
 * @brief Adjust the actions available in the main window
 * @param game Current game. May be nullptr
 */
void Controller::adjustActions(Game* game) const
{
    quint32 ActionsEnabled = 0;
    if (game != nullptr) {
        ActionsEnabled |= SAVE_GAME_AS_ENABLED | SAVE_ALL_GAMES_ENABLED| CLOSE_CURRENT_GAME_ENABLED | EDIT_CURRENT_GAME_NAME;
        if ((game->fullfilename().size() != 0) && (game->modified())) {
            ActionsEnabled |= SAVE_GAME_ENABLED;
        }
    }
    MainWindow::get()->adjustActions(ActionsEnabled);
}

/**
 * @brief Set the title bar of the main window according to the current opened file
 * @param game Current game. May be nullptr if there is no current game
 */
void Controller::adjustTitleBar(Game* game) const
{
    QString title(APPLICATION_NAME);
    if (game != nullptr) {
        if (!game->fullfilename().isEmpty()) {
            title.append(" - [ ").append(game->fullfilename()).append(" ]");
        }
        title.append(" - ").append(game->name());
    }
    MainWindow::get()->setWindowTitle(title);
}

/***********************************************************
 *
 *          New / Open / Save / Save as / Save all / Close / Close all mechanism
 *
 ***********************************************************/

/**
 * @brief Create a new game
 *
 * A game needs a name. To avoid a useless creation/destruction if the name input is cancelled,
 * this method prompts for a name, then sends it to the game when created
 */
void Controller::newGame()
{
    QString name = UiEditGameName::newGameName();
    if (!name.isEmpty()) {
        Game* game = new Game(name);                      // Create the game
        GameUi* ui = new GameUi;                          // Create the ui
        GameList.append(QPair<Game*, GameUi*>(game, ui)); // Push the game/ui pair
        game->populateUi();                               // Now the game can fill the ui
        MainWindow::get()->addGameUi(ui, name);           // Add it to the main window
    }
}

/**
 * @brief Open a game from a file
 */
void Controller::openGame()
{
    QString filename = QFileDialog::getOpenFileName(MainWindow::get(), tr("Open a game"), QDir::homePath(), GAME_FILE_FILTER);
    if (!filename.isEmpty()) {
        Game* game = Game::open(filename);
        if (game == nullptr) {
            return;
        }
        GameUi* ui = new GameUi;
        GameList.append(QPair<Game*, GameUi*>(game, ui));
        game->populateUi();
        MainWindow::get()->addGameUi(ui, game->name());
    }
}

/**
 * @brief Save a game which has already a filename
 *
 * This method is called by a user request in the main window
 *
 * @param ui Ui of the game to save
 */
void Controller::saveGame(QWidget* ui) const
{
    saveGame(gameOf(static_cast<GameUi*>(ui)));
}

/**
 * @brief Save a game
 * @param game Game
 */
bool Controller::saveGame ( Game* game ) const
{
    Q_ASSERT(game != nullptr);
    if (game->save()) {
        adjustActions(game);
        adjustTitleBar(game);
        return true;
    }
    return false;
}

/**
 * @brief Request a filename to save a game to a file
 *
 * This method is called by a user request in the main window
 *
 * @param ui Ui of the game to save
 */
void Controller::saveGameAs(QWidget* ui) const
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
bool Controller::saveGameAs(Game* game) const
{
    QString filename = QFileDialog::getSaveFileName(MainWindow::get(), QString(tr("Save game %1")).arg(game->name()), QDir::homePath(), GAME_FILE_FILTER);
    if (filename.isEmpty()) {
        return false;
    }
    if (QFileInfo(filename).suffix() != QString(GAME_FILE_EXTENSION)) {
        filename.append(QString(".%1").arg(GAME_FILE_EXTENSION));
    }
    game->setFilename(filename);
    return saveGame(game);
}

/**
 * @brief Browse all the games, save the ones which have a file, and prompt for the ones which have been newly created
 * @return void
 */
void Controller::saveAllGames() const
{
    for (int i = 0; i < GameList.size(); i++) {
        Game* game = GameList[i].first;
        if (game->modified()) {
            if (game->fullfilename().size() == 0) {
                saveGameAs(game);
            } else {
                saveGame(game);
            }
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
                if (!game->save()) {
                    return false; // Something failed
                }
            }
        }
    }

    // Ok, modifications saved or discarded, destroy the game and its ui
    GameUi* ui = gameUiOf(game);
    MainWindow::get()->RemoveGameUi(ui);
    delete ui;
    delete game;
    GameList.removeOne(QPair<Game*, GameUi*>(game, ui));
    return true;
}

/***********************************************************
 *
 *          Slots called by the main window, and which address the whole application
 *
 ***********************************************************/

bool Controller::appCloseRequested()
{
    while (GameList.size() != 0) {
        if (!closeGame(GameList.last().first)) {
            return false; // Game closing aborted by the user or failed
        }
    }
    return true; // All games closed succesfully
}

/**
 * @brief Message thrown by the main window to say that the current displayed game is changing
 *
 * @param ui Ui of the new current game
 */
void Controller::newCurrentUi(QWidget* ui) const
{
    GameUi* gameui = static_cast<GameUi*>(ui);
    Game* game = gameOf(gameui);
    adjustTitleBar(game);
    adjustActions(game);
}

QString Controller::gameNameEditRequested ( QWidget* ui)
{
    Game* game = gameOf(static_cast<GameUi*>(ui));
    if (game != nullptr) {
        QString newname = UiEditGameName::editGameName(game->name());
        if (newname.size() != 0) {
            game->setName(newname);
            adjustActions(game);
            adjustTitleBar(game);
        }
    }
    return game->name();
}
