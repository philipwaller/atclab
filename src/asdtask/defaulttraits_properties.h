#ifndef DEFAULTTRAITS_PROPERTIES_H
#define DEFAULTTRAITS_PROPERTIES_H

//#include <QExplicitlySharedDataPointer>
#include <QSharedDataPointer>


namespace asd {
namespace Traits {


class PropertiesData;


class Properties
{
public:
    Properties();
    Properties(const Properties &);
    ~Properties();

    Properties& operator=(const Properties &);

    qreal cruisingAlt();
    qreal cruisingVel();
    qreal acceleration();
    qreal climbRate();

    void setCruisingAlt(qreal);
    void setCruisingVel(qreal);
    void setAcceleration(qreal);
    void setClimbRate(qreal);


private:
//    QExplicitlySharedDataPointer<PropertiesData> data_;
    QSharedDataPointer<PropertiesData> data_;

};


}
}


#endif // DEFAULTTRAITS_PROPERTIES_H
