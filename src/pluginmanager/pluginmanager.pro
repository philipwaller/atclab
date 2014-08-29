#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:30:33
#
#-------------------------------------------------

QT       -= gui

TARGET =    pluginmanager
TEMPLATE =  lib
CONFIG +=   staticlib


SOURCES += \
    pluginmanager.cpp

HEADERS += \
    pluginmanager.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")
