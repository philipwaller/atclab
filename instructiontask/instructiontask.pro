#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T16:15:34
#
#-------------------------------------------------

QT      -= gui
QT      += widgets


TARGET =    instructiontask
TEMPLATE =  lib
CONFIG +=   plugin c++11
VERSION =   1.0.0
DESTDIR =   ../main/atclab.app/Contents/PlugIns


SOURCES += \
    instructiontask.cpp \
    instructiontaskview.cpp \
    instructiontaskfactory.cpp

HEADERS += \
    instructiontask.h \
    instructiontaskview.h \
    instructiontaskfactory.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    instructiontaskview.ui


include(../plugininterface/plugininterface.pri)
