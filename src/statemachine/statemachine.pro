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
    stringtransition.cpp \
    state.cpp \
    interuptstate.cpp \
    finalstate.cpp \
    stringevent.cpp

HEADERS += \
    statechart.h \
    statechartbuilder.h \
    stringtransition.h \
    state.h \
    interuptstate.h \
    finalstate.h \
    stringevent.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")
