#ifndef GAME_HPP
#define GAME_HPP

#include <QList>
#include <QString>
#include <QObject>
#include "BOTimer.hpp"
#include "FException.hpp"
#include "CyclicTimer.hpp"
#include "CyclicTimerSpec.hpp"
#include "CyclicTimerData.hpp"

class Game : public QObject
{
    Q_OBJECT

  public:
    Game();
    explicit Game(QString name);
    ~Game();
    void populateUi();
    bool modified() const;
    QString name() const;
    void setName(QString name);
    QString fullfilename() const;
    void open(QString filename) throw(const FException &);
    void save() throw(const FException &);
    void setFilename(QString filename);

    CyclicTimerSpec* cyclicTimerSpec();
    void newCyclicTimer(CyclicTimerData* data);

  private:
    Q_DISABLE_COPY(Game)
    QList<BOTimer*> BOTimerList;
    QList<CyclicTimer*> CyclicTimerList;
    QString Name;
    QString FullFilename;
    bool Modified;
};

#endif // GAME_HPP
