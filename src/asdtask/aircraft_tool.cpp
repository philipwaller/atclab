#include "aircraft_tool.h"

#include "aircraft.h"

#include <QDebug>
#include <QGraphicsLineItem>


//------------------------------------------------------------------------------
// asd::Aircraft::Tool
//

/**
 * @brief asd::Aircraft::Tool::Tool
 * @param parent
 */
asd::Aircraft::Tool::Tool(Sprite *aircraft, QObject *parent)
        : QObject(parent)
        , aircraft_(aircraft)
{}

/**
 * @brief asd::Aircraft::Tool::~Tool
 */
asd::Aircraft::Tool::~Tool() {}


//------------------------------------------------------------------------------
// asd::Aircraft::ShortRouteProbe
//

asd::Aircraft::ShortRouteProbe::ShortRouteProbe(Sprite *aircraft, QObject *parent)
        :Tool(aircraft, parent)
        ,probe_(0)
{}

asd::Aircraft::ShortRouteProbe*
asd::Aircraft::ShortRouteProbe::create(Sprite *aircraft) {
    ShortRouteProbe *srp = new ShortRouteProbe(aircraft);
    srp->probe_ = new QGraphicsLineItem(aircraft);
    srp->update();

    // connect here
    QObject::connect(
            aircraft->signaller(), &SpriteSignaller::path_updated,
            srp, &ShortRouteProbe::update
        );

    return srp;
}

asd::Aircraft::ShortRouteProbe::~ShortRouteProbe() {
    delete probe_;
}

void asd::Aircraft::ShortRouteProbe::update() {
    qreal vel = aircraft_->current_speed();
    qreal dx  = aircraft_->current_deltaX() * 100; //vel;
    qreal dy  = aircraft_->current_deltaY() * 100; //vel;
    probe_->setLine(0, 0, dx, dy);
}


//------------------------------------------------------------------------------
// asd::Aircraft::HistoryTool
//

asd::Aircraft::HistoryTool::HistoryTool(Sprite *aircraft, QObject *parent)
        :Tool(aircraft, parent)
{}

asd::Aircraft::HistoryTool*
asd::Aircraft::HistoryTool::create(Sprite *aircraft) {
        HistoryTool *history = new HistoryTool(aircraft);
        history->update();

        QObject::connect(
                aircraft->signaller(), &SpriteSignaller::position_updated,
                history, &HistoryTool::update
            );

        return history;
}


void asd::Aircraft::HistoryTool::update() {
    createPoint();
}

asd::Aircraft::HistoryTool::~HistoryTool() {
    while (!dots_.isEmpty()) delete dots_.takeFirst();
}


void asd::Aircraft::HistoryTool::createPoint() {
    QGraphicsEllipseItem *dot = new QGraphicsEllipseItem;
    aircraft_->scene()->addItem(dot);
    dot->setPen(Qt::NoPen);
    dot->setBrush(Qt::red);
    dot->setRect(-5,-5,10,10);
    dot->setPos(aircraft_->current_x(), aircraft_->current_y());

    dots_.push_front(dot);
    if (10 < dots_.size()) {
        QGraphicsEllipseItem* last = dots_.takeLast();
        delete last;
    }
}

