#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T10:22:30
#
#-------------------------------------------------

QT         -= gui
QT         += widgets

TARGET      = asdtask
TEMPLATE    = lib
CONFIG     += plugin c++11

VERSION     = $${CURRENT_VERSION}
DESTDIR     = $${PLUGIN}

SOURCES +=  \
            airsituationdisplay.cpp \
            scalecrosshair.cpp \
            sector.cpp \
            route.cpp \
            waypoint.cpp \
            aircraft.cpp \
            aircraft_properties.cpp \
            route_properties.cpp \
            sector_properties.cpp \
            waypoint_properties.cpp \
            scale_properties.cpp \
            asd_properties.cpp \
            aircraft_traits.cpp \
            defaulttraits.cpp \
            realnumberobject.cpp \
            defaulttraits_properties.cpp \
            aircraft_tool.cpp \
    asdtask.cpp \
    asdtaskview.cpp \
    asdtaskfactory.cpp

HEADERS  += \
            airsituationdisplay.h \
            scalecrosshair.h \
            sector.h \
            route.h \
            waypoint.h \
            aircraft.h \
            aircraft_properties.h \
            route_properties.h \
            sector_properties.h \
            waypoint_properties.h \
            scale_properties.h \
            asd_properties.h \
            aircraft_traits.h \
            defaulttraits.h \
            realnumberobject.h \
            defaulttraits_properties.h \
            aircraft_tool.h \
    asdtask.h \
    asdtaskview.h \
    asdtaskfactory.h

include($${SRCDIR}/plugininterface/plugininterface.pri)

message("!")
message("!  $${_PRO_FILE_}")
message("!")

FORMS += \
    asdtaskview.ui

