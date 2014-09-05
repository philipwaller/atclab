#-------------------------------------------------
#
# Project created by QtCreator 2014-03-06T10:31:27
#
#-------------------------------------------------

QT       -= gui
QT       += widgets


TARGET = consenttask
TEMPLATE = lib
CONFIG += plugin c++11

VERSION = $${CURRENT_VERSION}
DESTDIR = $${PLUGIN}


SOURCES += \
    consenttask.cpp \
    consenttaskview.cpp \
    consenttaskfactory.cpp

HEADERS += \
    consenttask.h\
    consenttaskview.h \
    consenttaskfactory.h

FORMS += \
    consenttaskview.ui

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")
