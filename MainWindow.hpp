#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QMainWindow>
#include <QCloseEvent>

/**
 * @brief The main window class
 *
 * This class is a singleton. All dialogs needs to access a pointer to the instance in order to be centered
 */
class MainWindow : public QMainWindow
{
  public:
    ~MainWindow();
    static MainWindow* get();
    static MainWindow* realInstance();
    void closeEvent(QCloseEvent* event) override;
    void addGameUi(QWidget* ui, QString name);
    void RemoveGameUi(QWidget* ui);
    void adjustActions(quint32 ActionsEnabled);
    void newCyclicTimer();
    void editCyclicTimer();
    void removeCyclicTimer();
    QAction* actionNewCyclicTimer() const;
    QAction* actionEditCyclicTimer() const;
    QAction* actionRemoveCyclicTimer() const;

  private:
    Q_DISABLE_COPY(MainWindow)
    MainWindow();
    void translate();
    void saveGame();
    void saveGameAs();
    void closeCurrentGame();
    void currentGameChanged(int);
    void gameCloseRequested(int index);
    void gameNameEditRequested(int index);
    void editCurrentGameName();

    // Actions
    QAction* ActionNewGame;
    QAction* ActionOpenGame;
    QAction* ActionSaveGame;
    QAction* ActionSaveAsGame;
    QAction* ActionSaveAllGames;
    QAction* ActionCloseCurrentGame;
    QAction* ActionQuitApplication;
    QAction* ActionAboutQt;
    QAction* ActionEditGameName;
    QAction* ActionNewCyclicTimer;
    QAction* ActionEditCyclicTimer;
    QAction* ActionRemoveCyclicTimer;

    // Game menus
    QMenu* MenuGame;
    QMenu* MenuEdit;
    QMenu* MenuCyclicTimers;
    QMenu* MenuHelp;

    // Central widget
    QTabWidget* tabs;
};

/**
 * @brief Actions status
 *
 * Allow the Controller to enable/disable actions, according to the current game status
 */
#define SAVE_GAME_ENABLED 1 << 0
#define SAVE_GAME_AS_ENABLED 1 << 1
#define SAVE_ALL_GAMES_ENABLED 1 << 2
#define CLOSE_CURRENT_GAME_ENABLED 1 << 3
#define EDIT_CURRENT_GAME_NAME_ENABLED 1 << 4
#define NEW_CYCLIC_TIMER_ENABLED 1 << 5
#define EDIT_CYCLIC_TIMER_ENABLED 1 << 6
#define REMOVE_CYCLIC_TIMER_ENABLED 1 << 7

#endif // MAIN_WINDOW_HPP
