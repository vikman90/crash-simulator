#-------------------------------------------------
#
# Project created by QtCreator 2012-05-21T20:26:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = crash
TEMPLATE = app


SOURCES += main.cpp \
    widget.cpp \
    map.cpp \
    road.cpp \
    cross.cpp \
    hroad.cpp \
    vroad.cpp

HEADERS  += \
    widget.h \
    map.h \
    road.h \
    cross.h \
    hroad.h \
    vroad.h

FORMS    += \
    widget.ui

RESOURCES += \
    images.qrc

RC_FILE = icon.rc
