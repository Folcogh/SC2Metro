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
    Game(QString name);
    ~Game();
    void populateUi();
    bool modified();

  private:
    Q_DISABLE_COPY(Game)
    QList<BOTimer*> BOTimerList;
    QList<CyclicTimer*> CyclicTimerList;
    QString Name;
    bool Modified;
};

#endif // GAME_HPP
