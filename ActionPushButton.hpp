#ifndef ACTION_PUSH_BUTTON_HPP
#define ACTION_PUSH_BUTTON_HPP

#include <QObject>
#include <QAction>
#include <QPushButton>

/**
 * @brief Provide a QPushButton associated to a QAction
 */
class ActionPushButton : public QPushButton {
    Q_OBJECT

  public:
    ActionPushButton(QAction* action, QWidget* parent = nullptr);
    ~ActionPushButton();
    void setAction(QAction* action);
    void removeAction();

  private:
    Q_DISABLE_COPY(ActionPushButton)
    QAction* Action;
    void updateAction();
};

#endif // ACTION_PUSH_BUTTON_HPP
