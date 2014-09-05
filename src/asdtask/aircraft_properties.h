#ifndef AIRCRAFT_PROPERTIES_H
#define AIRCRAFT_PROPERTIES_H


#include <QExplicitlySharedDataPointer>
#include <QFont>
#include <QPen>


namespace asd {
namespace AircraftSprite {


class PropertiesData;


class Properties
{
public:
    Properties();
    Properties(const Properties &);
    Properties &operator=(const Properties &);

    void setFont(QFont font);
    void setOutlinePen(QPen pen);
    void setBrush(QBrush brush);
    void setSize(qreal size);
    void setLayer(int layer);
    void setCallout(int callout);
    void setPen(QPen pen);

    QFont font();
    QPen outlinePen();
    QBrush brush();
    qreal size();
    int layer();
    int callout();
    QPen pen();

    ~Properties();
    
private:
    QExplicitlySharedDataPointer<PropertiesData> data_;
};


} // namespace AircraftSprite
} // namespace asd


#endif // AIRCRAFT_PROPERTIES_H
