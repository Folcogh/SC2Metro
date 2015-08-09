#include "NativeEventFilter.hpp"
#include "windows.h"
#include <QApplication>
#include <QDebug>
#include <QString>

NativeEventFilter::NativeEventFilter()
{
    count = 0;
}

bool NativeEventFilter::nativeEventFilter(const QByteArray& eventType, void* message, long*)
{
    if (eventType == "windows_dispatcher_MSG")
    {
        MSG* msg = static_cast<MSG*>(message);

        count++;
        qDebug() << QString("Event count: %1. Message: %2").arg(count).arg(msg->message);

        if (msg->message == WM_HOTKEY)
        {
            emit hotkeyPressed();
            return true;
        }
    }
    return false;
}
