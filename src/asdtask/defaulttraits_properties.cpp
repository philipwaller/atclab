#include "defaulttraits_properties.h"
#include <QSharedData>


class asd::Traits::PropertiesData : public QSharedData
{
private:
    static constexpr qreal CRUISING_ALT = 40000.0;      // feet?
    static constexpr qreal CRUISING_VEL = 1.10;         // knots?
    static constexpr qreal ACCELERATION = 0.00001;      // knots/sec?
    static constexpr qreal CLIMB_RATE   = 0.1;          // feet/min?

public:
    PropertiesData()
            : cruisingAlt(CRUISING_ALT)
            , cruisingVel(CRUISING_VEL)
            , acceleration(ACCELERATION)
            , climbRate(CLIMB_RATE)
    {}
    PropertiesData(PropertiesData &other)
            : QSharedData(other)
            , cruisingAlt(other.cruisingAlt)
            , cruisingVel(other.cruisingVel)
            , acceleration(other.acceleration)
            , climbRate(other.climbRate)
    {}
    ~PropertiesData() {}

    qreal cruisingAlt;
    qreal cruisingVel;
    qreal acceleration;
    qreal climbRate;

};

//
//
//

asd::Traits::Properties::Properties()
        : data_(new asd::Traits::PropertiesData)
{}

asd::Traits::Properties::Properties(const asd::Traits::Properties & other)
        : data_(other.data_)
{}

asd::Traits::Properties::~Properties() {}

asd::Traits::Properties&
asd::Traits::Properties::operator=(const asd::Traits::Properties &rhs)
{
    if (this != &rhs)
            data_.operator=(rhs.data_);
    return *this;
}

qreal asd::Traits::Properties::cruisingAlt() { return data_->cruisingAlt; }
qreal asd::Traits::Properties::cruisingVel() { return data_->cruisingVel; }
qreal asd::Traits::Properties::acceleration() { return data_->acceleration; }
qreal asd::Traits::Properties::climbRate() { return data_->climbRate; }

void asd::Traits::Properties::setCruisingAlt(qreal alt) { data_->cruisingAlt = alt; }
void asd::Traits::Properties::setCruisingVel(qreal vel) { data_->cruisingVel = vel; }
void asd::Traits::Properties::setAcceleration(qreal accel) { data_->acceleration = accel; }
void asd::Traits::Properties::setClimbRate(qreal rate) { data_->climbRate = rate; }
