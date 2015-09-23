#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T20:43:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tanks
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        gamewidget.cpp

HEADERS  += gamewidget.h \
    GameField/fieldelement.h \
    GameField/map.h \
    Helpers/gameconstants.h \
    States/state.h \
    States/stategame.h \
    States/stateloading.h \
    States/statemenu.h \
    Tanks/basetank.h \
    Tanks/bullet.h \
    Tanks/hardtank.h \
    Tanks/lighttank.h \
    Tanks/mediumtank.h \
    game.h \
    Helpers/log.h \
    Helpers/movable.h \
    Helpers/collidable.h \
    Tanks/botlogic.h \
    States/stateoptions.h \
    States/stateabout.h \
    States/stateratings.h \
    Tanks/factory.h

RESOURCES += \
    files.qrc \
    tanks.qrc
