#ifndef DEFAULTTRAITS_H
#define DEFAULTTRAITS_H


#include <QtCore>
#include "aircraft_traits.h"
#include "defaulttraits_properties.h"


namespace asd {
namespace Aircraft {


class DefaultTraits : public Traits
{
public:
//    explicit DefaultTraits();
    explicit DefaultTraits(asd::Traits::Properties properties);
//    explicit DefaultTraits(const DefaultTraits &);

    virtual qreal cruising_altitude();
    virtual qreal cruising_speed();
    virtual qreal acceleration();
    virtual qreal climb_rate();

private:
    asd::Traits::Properties properties_;

};


}
}

#endif // DEFAULTTRAITS_H
