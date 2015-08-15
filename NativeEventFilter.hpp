#ifndef NATIVEEVENTFILTER_HPP
#define NATIVEEVENTFILTER_HPP

#include <QObject>
#include <QAbstractNativeEventFilter>

class NativeEventFilter : public QObject, public QAbstractNativeEventFilter
{
        Q_OBJECT
    public:
        NativeEventFilter();
        virtual bool nativeEventFilter(const QByteArray &, void *message, long *) Q_DECL_OVERRIDE;

    private:
        Q_DISABLE_COPY(NativeEventFilter)

    signals:
        void hotkeyPressed();
};

#endif // NATIVEEVENTFILTER_HPP
