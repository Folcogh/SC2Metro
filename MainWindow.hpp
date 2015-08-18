#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QMenu>
#include <QAction>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
  public:
    MainWindow();
    ~MainWindow();

  private:
    Q_DISABLE_COPY(MainWindow);
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
