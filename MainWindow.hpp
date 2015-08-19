#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMenu>
#include <QAction>
#include <QMainWindow>

/**
 * @brief The main window class
 *
 * This class is a singleton. All dialogs needs to access a pointer to the
 *instance in order to be centered
 */
class MainWindow : public QMainWindow
{
  public:
    ~MainWindow();
    static MainWindow* get();
    static MainWindow* realInstance();

  private:
    Q_DISABLE_COPY(MainWindow)
    MainWindow();
    void translate();

    // Application-wide actions
    QAction* ActionNewGame;
    QAction* ActionOpenGame;
    QAction* ActionSaveGame;
    QAction* ActionSaveAsGame;
    QAction* ActionSaveAllGames;
    QAction* ActionCloseCurrentGame;
    QAction* ActionQuitApplication;

    // Game menu
    QMenu* MenuGame;
};

#endif // MAIN_WINDOW_HPP
