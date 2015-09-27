#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QList>
#include <QPair>
#include <QObject>
#include <QTableWidgetItem>
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
    void saveGame(QWidget* ui) const;
    void saveGameAs(QWidget* ui) const;
    void saveAllGames() const;
    void newCurrentUi(QWidget* ui) const;
    void gameCloseRequested(QWidget* ui);
    bool appCloseRequested();
    QString gameNameEditRequested(QWidget* ui);
    void newCyclicTimer(QWidget* widget);
    void cyclicTimerCheckChanged(QWidget* widget, QTableWidgetItem* item);
    void cyclicTimerSelectionChanged(QWidget* widge);

  private:
    Q_DISABLE_COPY(Controller)
    Controller();
    Game* gameOf(GameUi* ui) const;
    GameUi* gameUiOf(Game* game) const;
    bool saveGame(Game* game) const;
    bool saveGameAs(Game* game) const;
    bool closeGame(Game* game);
    void adjustActions(Game* game) const;
    void adjustTitleBar(Game* game) const;
    QList<QPair<Game*, GameUi*>> GameList;
};

#endif // CONTROLLER_HPP
