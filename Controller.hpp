#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QList>
#include <QPair>
#include <QObject>
#include "Game.hpp"
#include "GameUi.hpp"

// This class is a singleton
class Controller : public QObject
{
    Q_OBJECT

  public:
    Controller();
    ~Controller();
    static Controller* get(); // Classic instance getter

    // Slots connected from the main window
public slots:
    void newGame();
    void openGame();
    void saveGame();
    void saveGameAs();
    void saveAllGames();
    void closeCurrentGame();

  private:
    Q_DISABLE_COPY(Controller);
    QList<QPair<Game*, GameUi*>> GameList;
    QPair<Game*, GameUi*>* CurrentGame;
};

#endif // CONTROLLER_HPP
