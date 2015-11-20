#ifndef EDITGAMENAME_HPP
#define EDITGAMENAME_HPP

#include <QDialog>

namespace Ui {
    class EditGameName;
}

class EditGameName : public QDialog
{
        Q_OBJECT

    public:
        ~EditGameName();
        static QString editGameName(QString name);

    private:
        Q_DISABLE_COPY(EditGameName)
        explicit EditGameName(QString name);
        void adjustButtonOK();
        Ui::EditGameName *ui;
};

#endif // EDITGAMENAME_HPP
