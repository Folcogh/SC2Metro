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
    Timer.cpp \
    Modified.cpp \
    TableItem.cpp \
    DlgNewTimer.cpp \
    HotkeyInputWidget.cpp \
    TimerItem.cpp \
    NativeEventFilter.cpp \
    DlgEditTimer.cpp \
    SMDialog.cpp \
    DlgMisc.cpp \
    Log.cpp

HEADERS  += MainWindow.hpp \
    Timer.hpp \
    Modified.hpp \
    TableItem.hpp \
    DlgNewTimer.hpp \
    HotkeyInputWidget.hpp \
    TimerItem.hpp \
    SC2Metro.hpp \
    SMException.hpp \
    NativeEventFilter.hpp \
    DlgEditTimer.hpp \
    SMDialog.hpp \
    DlgMisc.hpp \
    Log.hpp

RESOURCES += \
    icon64.qrc \
    builtinsound.qrc \
    screens.qrc

DISTFILES += \
    Todo.txt \
    _clang-format

FORMS += \
    DlgMisc.ui
