#-------------------------------------------------
#
# Project created by QtCreator 2016-06-26T09:28:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SC2Metro
TEMPLATE = app

#LIBS += -lUser32 // Global hotkeys

SOURCES += main.cpp\
        MainWindow.cpp \
    DlgNewTimer.cpp \
    PredefinedTimer.cpp \
    Timer.cpp \
    TableItem.cpp \
    DlgEditTimer.cpp \
    Modification.cpp \
    DlgMisc.cpp \
    NativeEventFilter.cpp \
    KeyTranslator.cpp

HEADERS  += MainWindow.hpp \
    DlgNewTimer.hpp \
    PredefinedTimer.hpp \
    Timer.hpp \
    TableItem.hpp \
    DlgEditTimer.hpp \
    SC2Metro.hpp \
    Modification.hpp \
    DlgMisc.hpp \
    NativeEventFilter.hpp \
    KeyTranslator.hpp

FORMS    += MainWindow.ui \
    DlgNewTimer.ui \
    DlgEditTimer.ui \
    DlgMisc.ui

RESOURCES += \
    ToolbarIcon64.qrc \
    sounds.qrc

DISTFILES += \
    Todo.txt
