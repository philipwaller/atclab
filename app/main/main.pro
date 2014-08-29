#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:28:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR= $${DISTDIR}
TARGET = atclab
TEMPLATE = app

INCLUDEPATH +=  \
        $${SRCDIR}/statemachine  \
        $${SRCDIR}/pluginmanager  \
        $${SRCDIR}/scriptreader

SRCOUT = $${OUTDIR}/src
LIBS        += -L$${SRCOUT}/statemachine -lstatemachine
LIBS        += -L$${SRCOUT}/pluginmanager -lpluginmanager
LIBS        += -L$${SRCOUT}/scriptreader -lscriptreader


SOURCES += \
        main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")
