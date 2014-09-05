#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QGraphicsEllipseItem>
#include <QPen>

#include "waypoint_properties.h"


namespace asd {

class Waypoint : public QGraphicsEllipseItem
{
private:
    explicit Waypoint(QGraphicsItem *parent = 0);

public:
    class Builder {
    public:
        Builder(WaypointSprite::Properties properties);

        Builder* setName(const QString name);
        Builder* setLocation(qreal x, qreal y);

        Waypoint* build();

    private:
        WaypointSprite::Properties properties_;
        QString name_;
        QPointF location_;
    };

};

} // namespace asd

#endif // WAYPOINT_H
