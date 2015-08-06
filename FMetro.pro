#-------------------------------------------------
#
# Project created by QtCreator 2015-07-23T14:36:03
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FMetro
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    TimerUi.cpp \
    TimerComponent.cpp \
    LicenseUi.cpp \
    ReadmeUi.cpp

HEADERS  += MainWindow.hpp \
    TimerUi.hpp \
    TimerComponent.hpp \
    LicenseUi.hpp \
    ReadmeUi.hpp \
    Constants.hpp

FORMS    += MainWindow.ui \
    TimerUi.ui \
    LicenseUi.ui \
    ReadmeUi.ui

RESOURCES += \
    sounds.qrc \
    images.qrc

DISTFILES += \
    todo.txt \
    gpl.txt \
    Changelog.txt
