#include "route.h"


//------------------------------------------------------------------------------
//
//

asd::Route::Route(QGraphicsItem *parent) :
        QGraphicsPathItem(parent)
{
}


//------------------------------------------------------------------------------
//
//

asd::Route::Builder::Builder(RouteSprite::Properties properties) :
    properties_(properties),
    points_()
{}

asd::Route::Builder* asd::Route::Builder::addPoint(qreal x, qreal y) {
    points_.push_back(QPointF(x, y)); return this;
}

asd::Route* asd::Route::Builder::build() {
    asd::Route *route = new asd::Route;

    route->setPen(properties_.pen());
    route->setZValue(properties_.zlayer());

    if (!points_.isEmpty()) {
        QPainterPath path(points_.at(0));
        for (int i = 1; i < points_.size(); ++i)
                path.lineTo(points_.at(i));
        route->setPath(path);
    }

    return route;
}
