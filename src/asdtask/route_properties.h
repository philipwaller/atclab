#ifndef ROUTE_PROPERTIES_H
#define ROUTE_PROPERTIES_H

#include <QExplicitlySharedDataPointer>
#include <QPen>


namespace asd {
namespace RouteSprite {

class PropertiesData;

class Properties
{
public:
    Properties();
    Properties(const Properties &);
    Properties &operator=(const Properties &);
    ~Properties();

    void setPen(QPen pen);
    void setZlayer(int zlayer);

    QPen pen();
    int zlayer();

private:
    QExplicitlySharedDataPointer<PropertiesData> data_;
};


} // namespace RouteSprite
} // namespace asd


#endif // ROUTE_PROPERTIES_H
