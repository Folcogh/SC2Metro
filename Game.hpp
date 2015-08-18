#ifndef GAME_HPP
#define GAME_HPP

#include <QList>
#include <QObject>
#include "BOTimer.hpp"
#include "CyclicTimer.hpp"

class Game : public QObject
{
    Q_OBJECT

  public:
    Game();
    ~Game();

  private:
    Q_DISABLE_COPY(Game);
    QList<BOTimer*> BOTimerList;
    QList<CyclicTimer*> CyclicTimerList;
};

#endif // GAME_HPP
