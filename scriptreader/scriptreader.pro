#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T16:04:01
#
#-------------------------------------------------

QT       -= gui
QT       += xml


TARGET = scriptreader
TEMPLATE = lib
DEFINES += SCRIPTREADER_LIBRARY

SOURCES += \
        scriptreader.cpp

HEADERS += \
        scriptreader.h\
        scriptreader_global.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}
