#include "asd_properties.h"

#include <QDebug>
#include <QJsonDocument>


const QString asd::Properties::AIRCRAFT = "aircraft";
const QString asd::Properties::AC_CALLOUT = "callout";

const QString asd::Properties::TRAITS = "traits";
const QString asd::Properties::CRUISING_ALT = "cruising_alt";
const QString asd::Properties::CRUISING_VEL = "cruising_vel";
const QString asd::Properties::ACCELERATION = "acceleration";
const QString asd::Properties::CLIMB_RATE = "climb_rate";

const QString asd::Properties::WAYPOINT = "waypoint";
const QString asd::Properties::ROUTE = "route";
const QString asd::Properties::SECTOR = "sector";
const QString asd::Properties::SCALE = "scale";


asd::Properties asd::Properties::create(QByteArray data) {
    Properties properties;

    QJsonParseError parseError;
    QJsonDocument settings = QJsonDocument::fromJson(data, &parseError);

    if (QJsonParseError::NoError != parseError.error)
            qDebug()
                << "Json Parse Error : '" << parseError.errorString()
                << "' @ " << parseError.offset;

    else if (settings.isObject()) {
        QJsonObject jsonObj = settings.object();
        QJsonObject::const_iterator i = jsonObj.constBegin();
        for ( ; i != jsonObj.constEnd(); ++i)
                properties.dispatchItem(i.key(), i.value());
    }

    return properties;
}


asd::Properties::Properties() :
        aircraft_(),
        defaultTraits_(),
        waypoint_(),
        route_(),
        sector_(),
        scale_()
{}

void asd::Properties::dispatchItem(QString key, QJsonValue value) {
    QJsonObject item = value.toObject();

    if (AIRCRAFT == key)
            configureItem(item, &asd::Properties::aircraftConfiguration);
    else if (TRAITS == key)
            configureItem(item, &asd::Properties::defaultTraitsConfiguration);

    else if (WAYPOINT == key) configureWaypoint(item);
    else if (ROUTE == key) configureRoute(item);
    else if (SECTOR == key) configureSector(item);
    else if (SCALE == key) configureScale(item);
    else
            // log key-value data
            ;
}

void asd::Properties::configureItem(const QJsonObject config, configurationFn handler
) {
    QJsonObject::const_iterator it;
    for (it = config.constBegin(); it != config.constEnd(); ++it) {
        (this->*handler)(it.key(), it.value());
    }
}

void asd::Properties::aircraftConfiguration(
        const QString &key, const QJsonValue &value
) {
    if (AC_CALLOUT == key) aircraft_.setCallout(value.toInt());
    else
        // log key-value data
        ;
}

void asd::Properties::defaultTraitsConfiguration(
        const QString &key, const QJsonValue &value
) {
    if      (CRUISING_ALT == key)   defaultTraits_.setCruisingAlt(value.toDouble());
    else if (CRUISING_VEL == key)   defaultTraits_.setCruisingVel(value.toDouble());
    else if (ACCELERATION == key)   defaultTraits_.setAcceleration(value.toDouble());
    else if (CLIMB_RATE == key)     defaultTraits_.setClimbRate(value.toDouble());
    else
            // log key-value data
            ;

}


void asd::Properties::configureWaypoint(QJsonObject config) {
    Q_UNUSED(config)
}
void asd::Properties::configureRoute(QJsonObject config) {
    Q_UNUSED(config)
}
void asd::Properties::configureSector(QJsonObject config) {
    Q_UNUSED(config)
}
void asd::Properties::configureScale(QJsonObject config) {
    Q_UNUSED(config)
}
