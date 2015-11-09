#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "CyclicTimerData.hpp"
#include "CyclicTimerItem.hpp"

class GameUi : public QWidget
{
  public:
    GameUi();
    ~GameUi();
    void newCyclicTimer(CyclicTimerData* data);
    CyclicTimerData* currentCyclicTimerData();

  private:
    Q_DISABLE_COPY(GameUi)
    QTableWidget* CyclicTable;
    QPushButton* ButtonAddCyclic; // Useless ?
    QPushButton* ButtonEditCyclic;
    QPushButton* ButtonRemoveCyclic;

    void cyclicTableSelectionChanged();
    void cyclicTimerCheckChanged(QTableWidgetItem* item);
};

namespace Column
{
    enum {EnabledStatus, Sound, Period, Start, Terminate, Hotkey, Volume};
}

#endif // GAME_UI_HPP
