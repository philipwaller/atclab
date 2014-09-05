#ifndef SECTOR_H
#define SECTOR_H

#include <QGraphicsPolygonItem>
#include <QPen>

#include "sector_properties.h"


namespace asd {

class Sector : public QGraphicsPolygonItem
{
private:
    explicit Sector(QGraphicsItem *parent = 0);

public:
    class Builder {
    public:
        Builder(asd::SectorSprite::Properties properties);
        Builder* addPoint(qreal x, qreal y);
        Builder* setActive();

        Sector* build();

    private:
        asd::SectorSprite::Properties properties_;
        QVector<QPointF> points_;
        bool active_;

    }; // class Builder

};

} // namespace asd

#endif // SECTOR_H
