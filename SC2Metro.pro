#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T19:16:30
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SC2Metro
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TimerList.cpp \
    Timer.cpp \
    Modified.cpp \
    TableItem.cpp \
    DlgNewTimer.cpp \
    HotkeyInputWidget.cpp \
    TimerItem.cpp \
    SMException.cpp \
    NativeEventFilter.cpp \
    DlgEditTimer.cpp

HEADERS  += MainWindow.hpp \
    TimerList.hpp \
    Timer.hpp \
    Modified.hpp \
    TableItem.hpp \
    DlgNewTimer.hpp \
    HotkeyInputWidget.hpp \
    TimerItem.hpp \
    SC2Metro.hpp \
    SMException.hpp \
    NativeEventFilter.hpp \
    DlgEditTimer.hpp

RESOURCES += \
    icon64.qrc \
    builtinsound.qrc

DISTFILES += \
    Todo.txt
