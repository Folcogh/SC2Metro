#ifndef GAME_UI_HPP
#define GAME_UI_HPP

#include <QWidget>

class GameUi : public QWidget
{
  public:
    GameUi();
    ~GameUi();

  private:
    Q_DISABLE_COPY(GameUi);
};

#endif // GAME_UI_HPP
