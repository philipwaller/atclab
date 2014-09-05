#include "waypoint.h"

//------------------------------------------------------------------------------
//
//

asd::Waypoint::Waypoint(QGraphicsItem *parent) :
        QGraphicsEllipseItem(parent)
{}


//------------------------------------------------------------------------------
//
//

asd::Waypoint::Builder::Builder(asd::WaypointSprite::Properties propterties) :
        properties_(propterties),
        name_(),
        location_()
{}

asd::Waypoint::Builder* asd::Waypoint::Builder::setName(const QString name) {
    name_ = name; return this;
}

asd::Waypoint::Builder* asd::Waypoint::Builder::setLocation(qreal x, qreal y) {
    location_ = QPointF(x, y); return this;
}

asd::Waypoint* asd::Waypoint::Builder::build() {
    asd::Waypoint *waypoint = new asd::Waypoint;

    //
    // Properties
    //

    waypoint->setPen(properties_.pen());
    waypoint->setBrush(properties_.brush());
    waypoint->setZValue(properties_.zlayer());

    qreal size = properties_.size();
    waypoint->setRect(-size/2, -size/2, size, size);

    if (!name_.isEmpty()) {
        QGraphicsSimpleTextItem *text = new QGraphicsSimpleTextItem(waypoint);
        text->setPen(Qt::NoPen);
        text->setBrush(properties_.pen().brush());

        text->setText(name_);
    }

    waypoint->setPos(location_);

    return waypoint;
}
