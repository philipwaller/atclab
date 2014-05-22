#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T10:57:06
#
#-------------------------------------------------

QT       += xml

QT       -= gui

TARGET = scriptparser
TEMPLATE = lib

DEFINES += SCRIPTPARSER_LIBRARY

SOURCES += scriptparser.cpp

HEADERS += scriptparser.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}
