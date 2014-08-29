#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T16:04:01
#
#-------------------------------------------------

QT       -= gui
QT       += xml


TARGET = scriptreader
TEMPLATE = lib
CONFIG += staticlib c++11
DEFINES += SCRIPTREADER_LIBRARY

SOURCES += \
    scriptreader.cpp \
    scripthandler.cpp \
    elementreader.cpp \
    scripthandlertree.cpp \
    scripthandlertreebuilder.cpp

HEADERS += \
    scriptreader.h\
    scriptreader_global.h \
    scripthandler.h \
    elementreader.h \
    scripthandlertree.h \
    scripthandlertreebuilder.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

message("!")
message("!  $${_PRO_FILE_}")
message("!")
