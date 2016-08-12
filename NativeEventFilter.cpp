#include "NativeEventFilter.hpp"
#include "MainWindow.hpp"
#include "windows.h"
#include <QCoreApplication>

NativeEventFilter::NativeEventFilter()
{
    QCoreApplication::instance()->installNativeEventFilter(this);
}

bool NativeEventFilter::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
{
    (void)result;
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        if (msg->message == WM_HOTKEY) {
            return MainWindow::instance()->hotkeyReceived(msg->wParam);
        }
    }
    return false;
}
