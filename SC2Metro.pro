#-------------------------------------------------
#
# Project created by QtCreator 2016-07-23T19:16:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SC2Metro
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    TimerList.cpp \
    Timer.cpp \
    Modified.cpp \
    TableItem.cpp \
    DlgNewTimer.cpp

HEADERS  += MainWindow.hpp \
    TimerList.hpp \
    Timer.hpp \
    Modified.hpp \
    TableItem.hpp \
    DlgNewTimer.hpp

RESOURCES += \
    icon64.qrc \
    builtinsound.qrc

DISTFILES += \
    Todo.txt
