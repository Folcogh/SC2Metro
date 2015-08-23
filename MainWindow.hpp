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
    void currentGameChanged(int);
    void gameCloseRequested(int index);
    void RemoveGameUi(QWidget* ui);

  private:
    Q_DISABLE_COPY(MainWindow)
    MainWindow();
    void translate();
    void saveGame();
    void saveGameAs();
    void closeCurrentGame();

    // Application-wide actions
    QAction* ActionNewGame;
    QAction* ActionOpenGame;
    QAction* ActionSaveGame;
    QAction* ActionSaveAsGame;
    QAction* ActionSaveAllGames;
    QAction* ActionCloseCurrentGame;
    QAction* ActionQuitApplication;
    QAction* ActionAboutQt;

    // Game menu
    QMenu* MenuGame;
    QMenu* MenuHelp;

    // Central widget
    QTabWidget* tabs;
};

#endif // MAIN_WINDOW_HPP
