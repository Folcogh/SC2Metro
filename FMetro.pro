#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T21:13:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FMetro
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    StartPage.cpp \
    Game.cpp \
    EditGameName.cpp \
    CyclicTimer.cpp \
    DlgNewGame.cpp

HEADERS  += MainWindow.hpp \
    StartPage.hpp \
    Game.hpp \
    EditGameName.hpp \
    TimeFormat.hpp \
    CyclicTimer.hpp \
    Application.hpp \
    DlgNewGame.hpp \
    Race.hpp

FORMS    += MainWindow.ui \
    StartPage.ui \
    Game.ui \
    EditGameName.ui \
    DlgNewGame.ui

DISTFILES += \
    todo.txt

RESOURCES += \
    Pictures.qrc
