#ifndef ROUTE_H
#define ROUTE_H

#include <QGraphicsPathItem>
#include <QPen>

#include "route_properties.h"


namespace asd {

class Route : public QGraphicsPathItem
{
private:
    explicit Route(QGraphicsItem *parent = 0);

public:

    class Builder {
    public:
        Builder(RouteSprite::Properties properties);
        Builder* addPoint(qreal x, qreal y);

        Route* build();

    private:
        RouteSprite::Properties properties_;
        QVector<QPointF> points_;
    };

};

} // namespace asd

#endif // ROUTE_H
