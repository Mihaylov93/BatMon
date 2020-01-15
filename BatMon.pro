# Project created by QtCreator 2018-08-04T16:53:33

QT       += core gui widgets

TARGET = BatMon
TEMPLATE = app

INSTALLDIR =

DEFINES += QT_DEPRECATED_WARNINGS

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 release

SOURCES += \
        batteryinfo.cpp \
        main.cpp \
        batterywidget.cpp

HEADERS += \
        batteryinfo.hpp \
        batterywidget.h

FORMS += \
        batterywidget.ui

!travis {
    QMAKE_POST_LINK += $$quote(mkdir /home/cpi/apps/Menu/BatMon/)
    QMAKE_POST_LINK += $$quote(; cp -f $${PWD}/BatMon /home/cpi/apps/Menu/BatMon/BatMon)
    QMAKE_POST_LINK += $$quote(&& cp -f $${PWD}/BatMon.png /home/cpi/apps/Menu/BatMon/BatMon.png)
    QMAKE_POST_LINK += $$quote(&& cp -f $${PWD}/scripts/BatMon.sh /home/cpi/apps/Menu/BatMon/BatMon.sh)
}
