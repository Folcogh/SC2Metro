#ifndef NATIVEEVENTFILTER_HPP
#define NATIVEEVENTFILTER_HPP

#include <QObject>
#include <QByteArray>
#include <QAbstractNativeEventFilter>

class NativeEventFilter : public QObject, QAbstractNativeEventFilter
{
        Q_OBJECT

  public:
    NativeEventFilter();
    bool nativeEventFilter(const QByteArray& eventType, void* message, long* result) override;

    signals:
    void hotkeyReceived(int hotkeyId);
};

#endif // NATIVEEVENTFILTER_HPP
