#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
    class Game;
}

class Game : public QWidget
{
        Q_OBJECT

    public:
        Game(QString name, int race);
        ~Game();
        void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
        static Game* newGame();
        void editName();
        QString getName() { return m_name; }
        int getRace() { return m_race; }
        bool isModified();

    private:*
        Q_DISABLE_COPY(Game)
        Ui::Game *ui;
        QString m_name;
        int m_race;
        bool m_modified;
};

#endif // GAME_HPP
