#include "HotkeyInputWidget.hpp"
#include <windows.h>
#include <QKeyEvent>

HotkeyInputWidget::HotkeyInputWidget()
{
    this->setText(tr("Pess a key"));
    this->installEventFilter(this);
}

HotkeyInputWidget::~HotkeyInputWidget()
{
}

bool HotkeyInputWidget::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        // If the TAB or SHIRT+TAB is pressed, let Qt process the event to allow the standard widget browsing
        if (!((keyEvent->nativeVirtualKey() == VK_TAB) &&
              ((keyEvent->nativeModifiers() == 0) ||
               (keyEvent->nativeModifiers() == MOD_SHIFT)))) {

            return true;
        }
    }
    return QObject::eventFilter(object, event);
}
