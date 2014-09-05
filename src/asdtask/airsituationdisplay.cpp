#include "airsituationdisplay.h"

#include <QGraphicsView>
#include <QTimer>

#include "aircraft.h"
#include "route.h"
#include "scalecrosshair.h"
#include "sector.h"
#include "waypoint.h"


namespace asd {


AirSituationDisplay::AirSituationDisplay(QObject *parent) :
    QGraphicsScene(parent),
    aircraft_(),
    deactivatedAircraft_(),
    advanceTimer_(new QTimer(this))
{}

QWidget* AirSituationDisplay::view() {
    QGraphicsView *view = new QGraphicsView(this);
//    view->setTransform(QTransform::fromScale(0.75, 0.75));
    return view;
}

int AirSituationDisplay::updateInterval() {
    return advanceTimer_->interval();
}

void AirSituationDisplay::start() {
    advanceTimer_->start();
}

void AirSituationDisplay::advance() {
    QList<Aircraft::Sprite*>::iterator ac;
    for (ac = aircraft_.begin(); ac != aircraft_.end(); ++ac) {
        (*ac)->advance(updateInterval());
    }
    while (!deactivatedAircraft_.isEmpty()) {
        Aircraft::Sprite *deactAc = deactivatedAircraft_.takeFirst();
        aircraft_.removeOne(deactAc);
        this->removeItem(deactAc);
        delete deactAc;
    }
}

void AirSituationDisplay::deactivateAircraft(Aircraft::Sprite *aircraft) {
    deactivatedAircraft_.append(aircraft);
}


//------------------------------------------------------------------------------
//
//

AirSituationDisplay::Builder::Builder() {}

AirSituationDisplay::Builder::~Builder() {
    while (!items_.isEmpty())
            delete items_.dequeue();
}

AirSituationDisplay::Builder* AirSituationDisplay::Builder::setSceneRect(
        qreal x, qreal y, qreal w, qreal h
) {
    sceneRect_ = QRect(x, y, w, h);
    return this;
}

AirSituationDisplay::Builder* AirSituationDisplay::Builder::addItem(
        QGraphicsItem* item
) {
    items_.enqueue(item);
    return this;
}

AirSituationDisplay::Builder* AirSituationDisplay::Builder::setAdvance(
        int msec
) {
    advance_ = msec;
    return this;
}

AirSituationDisplay* AirSituationDisplay::Builder::build() {
    AirSituationDisplay *asd = new AirSituationDisplay;

    asd->setSceneRect(sceneRect_);

    while (!items_.isEmpty()) {
        QGraphicsItem* item = items_.dequeue();
        asd->addItem(item);
        Aircraft::Sprite* aircraft = dynamic_cast<Aircraft::Sprite*>(item);
        if (aircraft)
                asd->aircraft_.push_back(aircraft);
    }

    asd->advanceTimer_->setInterval(advance_);
    QObject::connect(
                asd->advanceTimer_, &QTimer::timeout,
                asd, &AirSituationDisplay::advance
            );

    return asd;
}


} // namespace asd
