#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QList>
#include <QPair>
#include <QObject>
#include "Game.hpp"
#include "GameUi.hpp"

/**
 * @brief Controller of the MVC pattern
 *
 * This class os a singleton, and dispatch the messages between the games and the interfaces.
 * It maintain a pairs list to allow them to communicate
 */
class Controller : public QObject
{
    Q_OBJECT

  public:
    ~Controller();
    static Controller* get();
    static Controller* realInstance();
    void newGame();
    void openGame();
    void saveGame(QWidget* ui);
    void saveGame(Game* game);
    void saveGameAs(QWidget* ui);
    void saveAllGames();
    void newCurrentUi(QWidget* ui);
    void gameCloseRequested(QWidget* ui);
    bool appCloseRequested();

  private:
    Q_DISABLE_COPY(Controller)
    Controller();
    Game* gameOf(GameUi* ui);
    GameUi* uiOf(Game* game);
    bool saveGameAs(Game* game);
    bool closeGame(Game* game);
    QList<QPair<Game*, GameUi*>> GameList;
};

#endif // CONTROLLER_HPP
