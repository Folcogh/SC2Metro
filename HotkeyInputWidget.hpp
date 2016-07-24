#ifndef HOTKEYINPUTWIDGET_HPP
#define HOTKEYINPUTWIDGET_HPP

#include <QEvent>
#include <QObject>
#include <QPushButton>

class HotkeyInputWidget: public QPushButton
{
    public:
        HotkeyInputWidget();
        ~HotkeyInputWidget();

    private:
        bool eventFilter(QObject* object, QEvent* event) override;
};

#endif // HOTKEYINPUTWIDGET_HPP
