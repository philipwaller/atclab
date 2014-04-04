#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:28:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = atclab
TEMPLATE = app

INCLUDEPATH += ../statemachine  ../pluginmanager
LIBS        += -L../statemachine -lstatemachine
LIBS        += -L../pluginmanager -lpluginmanager


SOURCES += \
        main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include(../plugininterface/plugininterface.pri)
