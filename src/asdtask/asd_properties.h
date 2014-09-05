#ifndef ASD_PROPERTIES_H
#define ASD_PROPERTIES_H


#include <QJsonObject>
#include <QString>


#include "aircraft_properties.h"
#include "defaulttraits_properties.h"
#include "route_properties.h"
#include "scale_properties.h"
#include "sector_properties.h"
#include "waypoint_properties.h"


namespace asd {


class Properties;
typedef void (Properties::*configurationFn)(const QString &key, const QJsonValue &value);


class Properties
{
public:
    static const QString AIRCRAFT;
    static const QString AC_CALLOUT;

    static const QString TRAITS;
    static const QString CRUISING_ALT;
    static const QString CRUISING_VEL;
    static const QString ACCELERATION;
    static const QString CLIMB_RATE;

    static const QString WAYPOINT;
    static const QString ROUTE;
    static const QString SECTOR;
    static const QString SCALE;


    static Properties create(QByteArray data);
    ~Properties() {}

    AircraftSprite::Properties aircraft() { return aircraft_; }
    Traits::Properties defaultTraits() { return defaultTraits_; }
    WaypointSprite::Properties waypoint() { return waypoint_; }
    RouteSprite::Properties route() { return route_; }
    SectorSprite::Properties sector() { return sector_; }
    ScaleSprite::Properties scale() { return scale_; }

private:
    explicit Properties();

    void dispatchItem(QString key, QJsonValue value);
    void configureItem(const QJsonObject config, configurationFn);

    void aircraftConfiguration(const QString &key, const QJsonValue &value);
    void defaultTraitsConfiguration(const QString &key, const QJsonValue &value);

    void configureWaypoint(QJsonObject config);
    void configureRoute(QJsonObject config);
    void configureSector(QJsonObject config);
    void configureScale(QJsonObject config);


    AircraftSprite::Properties aircraft_;
    Traits::Properties defaultTraits_;
    WaypointSprite::Properties waypoint_;
    RouteSprite::Properties route_;
    SectorSprite::Properties sector_;
    ScaleSprite::Properties scale_;

};


} // namespace asd


#endif // ASD_PROPERTIES_H
