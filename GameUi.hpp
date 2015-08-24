#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>

class GameUi : public QWidget
{
  public:
    GameUi();
    ~GameUi();

  private:
    Q_DISABLE_COPY(GameUi)
    void newCyclicTimer();

    QTableWidget* CyclicTable;
    QPushButton* ButtonAddCyclic; // Useless ?
    QPushButton* ButtonEditCyclic;
    QPushButton* ButtonRemoveCyclic;
};

#endif // GAME_UI_HPP
