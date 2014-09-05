#ifndef WAYPOINT_PROPERTIES_H
#define WAYPOINT_PROPERTIES_H


#include <QExplicitlySharedDataPointer>
#include <QPen>


namespace asd {
namespace WaypointSprite {


class PropertiesData;


class Properties
{
public:
    Properties();
    Properties(const Properties &);
    Properties &operator=(const Properties &);
    ~Properties();

    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setSize(qreal size);
    void setZlayer(int zlayer);

    QPen pen();
    QBrush brush();
    qreal size();
    int zlayer();

private:
    QExplicitlySharedDataPointer<PropertiesData> data_;
};


} // namespace WaypointSprite
} // namespace asd


#endif // WAYPOINT_PROPERTIES_H
