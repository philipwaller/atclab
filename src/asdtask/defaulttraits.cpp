#include "defaulttraits.h"


//asd::Aircraft::DefaultTraits::DefaultTraits()
//        : properties_()
//{}

asd::Aircraft::DefaultTraits::DefaultTraits(asd::Traits::Properties properties)
        : properties_(properties)
{}

//asd::Aircraft::DefaultTraits::DefaultTraits(const asd::Aircraft::DefaultTraits &rhs)
//        : properties_(rhs.properties_)
//{}

qreal asd::Aircraft::DefaultTraits::cruising_altitude() {
    return properties_.cruisingAlt();
}

qreal asd::Aircraft::DefaultTraits::cruising_speed() {
    return properties_.cruisingVel();
}

qreal asd::Aircraft::DefaultTraits::acceleration() {
    return
            current_velocity() < cleared_velocity()
            ?  properties_.acceleration()
            : -properties_.acceleration()
       ;
}
qreal asd::Aircraft::DefaultTraits::climb_rate() {
    return
            current_altitude() < cleared_altitude()
            ?  properties_.climbRate()
            : -properties_.climbRate()
       ;
}
