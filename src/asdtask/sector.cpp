#include "sector.h"


//------------------------------------------------------------------------------
//
//

asd::Sector::Sector(QGraphicsItem *parent) :
        QGraphicsPolygonItem(parent)
{}


//------------------------------------------------------------------------------
//
//

asd::Sector::Builder::Builder(asd::SectorSprite::Properties properties) :
    properties_(properties),
    points_(),
    active_(false)
{}

asd::Sector::Builder* asd::Sector::Builder::addPoint(qreal x, qreal y) {
    points_.push_back(QPointF(x, y)); return this;
}

asd::Sector::Builder* asd::Sector::Builder::setActive() {
    active_ = true; return this;
}

asd::Sector* asd::Sector::Builder::build() {
    asd::Sector *sector = new asd::Sector;

    sector->setPen(properties_.pen());
    sector->setBrush(active_ ? properties_.activeBrush() : properties_.brush());
    sector->setZValue(properties_.zlayer());

    sector->setPolygon(QPolygonF(points_));

    return sector;
}
