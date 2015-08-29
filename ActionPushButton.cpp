#include "ActionPushButton.hpp"

ActionPushButton::ActionPushButton(QAction* action, QWidget* parent)
    : QPushButton(parent)
    , Action(nullptr)
{
    setAction(action);
}

ActionPushButton::~ActionPushButton()
{
    removeAction();
}

void ActionPushButton::setAction(QAction* action)
{
    Q_ASSERT(action != nullptr);
    removeAction();
    Action = action;
    updateAction();
    connect(Action, &QAction::changed, this, &ActionPushButton::updateAction);
    if (Action->menu() == nullptr) {
        connect(this, &QPushButton::clicked, Action, &QAction::trigger);
    }
    else {
        setMenu(Action->menu());
    }
}

void ActionPushButton::removeAction()
{
    if (Action != nullptr) {
        disconnect(Action, &QAction::changed, this, &ActionPushButton::updateAction);
        if (menu() != nullptr) {
            disconnect(this, &QPushButton::clicked, Action, &QAction::trigger);
        }
        Action = nullptr;
    }
}

void ActionPushButton::updateAction()
{
    setIcon(Action->icon());
    setText(Action->text());
    setToolTip(Action->toolTip());
    setEnabled(Action->isEnabled());
    setVisible(Action->isVisible());
    setChecked(Action->isChecked());
    setShortcut(Action->shortcut());
    setStatusTip(Action->statusTip());
    setWhatsThis(Action->whatsThis());
    setCheckable(Action->isCheckable());
}
