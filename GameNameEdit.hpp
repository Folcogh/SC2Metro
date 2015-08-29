#ifndef GAME_NAME_EDIT_HPP
#define GAME_NAME_EDIT_HPP

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>

/**
 * @brief Create or edit the name of a game
 * Use the static method newGameName() to create a new name
 * Use the static method editGameName(QString) to edit an existing name
 */
class GameNameEdit : public QDialog
{
  public:
      GameNameEdit();
      explicit GameNameEdit(QString name);
      ~GameNameEdit();
    static QString newGameName();
    static QString editGameName(QString name);

  private:
    Q_DISABLE_COPY(GameNameEdit)
    void adjustButtonOk(const QString& text);
    QString commonEdit();

    QDialogButtonBox* buttons;
    QVBoxLayout* mainLayout;
    QLineEdit* nameEdit;
};

#endif // GAME_NAME_EDIT_HPP
