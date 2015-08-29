#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include "CyclicTimerData.hpp"

class GameUi : public QWidget
{
  public:
    GameUi();
    ~GameUi();
    void newCyclicTimer(CyclicTimerData* data);

  private:
    Q_DISABLE_COPY(GameUi)
    QTableWidget* CyclicTable;
    QPushButton* ButtonAddCyclic; // Useless ?
    QPushButton* ButtonEditCyclic;
    QPushButton* ButtonRemoveCyclic;
};

#endif // GAME_UI_HPP
