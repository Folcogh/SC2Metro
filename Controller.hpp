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
    void saveGame();
    void saveGameAs();
    void saveAllGames();
    void closeCurrentGame();

  private:
    Q_DISABLE_COPY(Controller)
    Controller();

    /**
     * @brief This list keeps the association between a game and its interface
     *
     */
    QList<QPair<Game*, GameUi*>> GameList;
    /**
     * @brief Point to the active pair in the main window
     *
     */
    QPair<Game*, GameUi*>* CurrentGame;
};

#endif // CONTROLLER_HPP

