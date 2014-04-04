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
VERSION = 1.0.0
DESTDIR = ../main/atclab.app/Contents/PlugIns


SOURCES += \
    consenttask.cpp \
    consenttaskview.cpp \
    consenttaskfactory.cpp

HEADERS += \
    consenttask.h\
    consenttaskview.h \
    consenttaskfactory.h

unix:!symbian {
    target.path = /usr/lib
    INSTALLS += target
}

include(../plugininterface/plugininterface.pri)

FORMS += \
    consenttaskview.ui
