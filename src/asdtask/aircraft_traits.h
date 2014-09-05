#ifndef AIRCRAFT_TRAITS_H
#define AIRCRAFT_TRAITS_H


#include <QtCore>


namespace asd {
namespace Aircraft {


//
//
//
class Sprite;


//
//
//
class Traits {

public:
    virtual ~Traits() {}

    void attach(const asd::Aircraft::Sprite *sprite);

    virtual qreal cruising_altitude() = 0;
    virtual qreal cruising_speed() = 0;
    virtual qreal acceleration() = 0;
    virtual qreal climb_rate() = 0;

    virtual qreal current_velocity();
    virtual qreal cleared_velocity();
    virtual qreal current_altitude();
    virtual qreal cleared_altitude();

protected:
    const asd::Aircraft::Sprite *sprite_;

};


} // namespace Aircraft
} // namespace asd


#endif // AIRCRAFT_TRAITS_H
