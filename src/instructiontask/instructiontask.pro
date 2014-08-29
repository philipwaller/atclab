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
VERSION = $${CURRENT_VERSION}
DESTDIR = $${PLUGIN}


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


include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")
