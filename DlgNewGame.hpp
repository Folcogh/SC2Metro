#ifndef DLGNEWGAME_HPP
#define DLGNEWGAME_HPP

#include <QDialog>
#include <QAbstractButton>
#include <QIcon>

namespace Ui {
    class DlgNewGame;
}

class DlgNewGame : public QDialog
{
        Q_OBJECT

    public:
        DlgNewGame();
        ~DlgNewGame();
        int getRace();
        QString getName();

    private:
        void raceClicked(QAbstractButton* button);
        void adjustButtonOk();
        Ui::DlgNewGame *ui;
        QIcon m_Protoss;
        QIcon m_ProtossGray;
        QIcon m_Terran;
        QIcon m_TerranGray;
        QIcon m_Zerg;
        QIcon m_ZergGray;
};

#endif // DLGNEWGAME_HPP
