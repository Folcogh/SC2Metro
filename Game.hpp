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
    explicit Game(QString name);
    ~Game();
    void populateUi();
    bool modified() const;
    QString name() const;
    QString fullfilename() const;
    bool save();
    void setFilename(QString filename);
    static Game* open(QString filename);
    void setName (QString name );

  private:
    Q_DISABLE_COPY(Game)
    QList<BOTimer*> BOTimerList;
    QList<CyclicTimer*> CyclicTimerList;
    QString Name;
    QString FullFilename;
    bool Modified;
};

#endif // GAME_HPP
