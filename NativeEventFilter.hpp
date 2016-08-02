#ifndef NATIVEEVENTFILTER_HPP
#define NATIVEEVENTFILTER_HPP

#include <QByteArray>
#include <QAbstractNativeEventFilter>

class NativeEventFilter : public QAbstractNativeEventFilter
{
    public:
        NativeEventFilter();
        bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;
};

#endif // NATIVEEVENTFILTER_HPP
