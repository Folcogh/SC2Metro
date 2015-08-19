#ifndef UI_EDIT_GAME_NAME_HPP
#define UI_EDIT_GAME_NAME_HPP

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
class UiEditGameName : public QDialog
{
  public:
    UiEditGameName();
    explicit UiEditGameName(QString name);
    ~UiEditGameName();
    static QString newGameName();
    static QString editGameName(QString name);

  private:
    Q_DISABLE_COPY(UiEditGameName)
    void adjustButtonOk(const QString& text);
    QString commonEdit();

    QDialogButtonBox* buttons;
    QVBoxLayout* mainLayout;
    QLineEdit* nameEdit;
};

#endif // UI_EDIT_GAME_NAME_HPP
