#include "NativeEventFilter.hpp"
#include "windows.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QAbstractEventDispatcher>

NativeEventFilter::NativeEventFilter()
{
    if (!RegisterHotKey((HWND)0, 1, MOD_ALT | MOD_SHIFT, 0x53))
    {
        QMessageBox::critical(NULL, "Hotkey error", "Can't register hotkey, it won't work");
    }
    QAbstractEventDispatcher::instance()->installNativeEventFilter(this);
}

bool NativeEventFilter::nativeEventFilter(const QByteArray&, void* message, long*)
{
//    if (eventType == "windows_dispatcher_MSG")
    {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY)
        {
            emit hotkeyPressed();
//            return true;
        }
    }
    return false;
}
