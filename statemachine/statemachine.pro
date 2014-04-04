#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:24:03
#
#-------------------------------------------------

QT      -= gui
QT      += widgets


TARGET =    statemachine
TEMPLATE =  lib
CONFIG +=   staticlib

SOURCES += \
    statechart.cpp \
    statechartbuilder.cpp \
    stringtransition.cpp

HEADERS += \
    statechart.h \
    statechartbuilder.h \
    stringtransition.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

include(../plugininterface/plugininterface.pri)
