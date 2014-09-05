#include "aircraft.h"

#include <QDebug>
#include <QFont>
#include <QFontMetrics>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPen>
#include <QTimer>

#include <QtMath>

#include "aircraft_tool.h"
#include "airsituationdisplay.h"
#include "defaulttraits.h"


namespace asd {
namespace Aircraft {


//------------------------------------------------------------------------------
//
//

Sprite::Sprite(QGraphicsItem *parent)
        : QGraphicsEllipseItem(parent)
        , callsign_()
        , type_()
        , path_()
        , pathPoint_()
        , closedPath_(false)
        , state_()
        , traits_()
        , level_required_(false)
        , signaller_()
        , short_route_probe_(0)
        , history_tool_()
{
}

void Sprite::advance(int ms) {

    state_->timetag += ms;

    // controller status ?? @phase 1

    advance_position(ms);
    advance_altitude(ms);
    advance_speed(ms);

    update_display();
}

qreal Sprite::current_speed() const { return state_->vel; }
qreal Sprite::current_deltaX() const { return (*pathPoint_).dx; }
qreal Sprite::current_deltaY() const { return (*pathPoint_).dy; }
quint32 Sprite::current_timetag() const { return state_->timetag; }
qreal Sprite::current_x() const { return state_->x; }
qreal Sprite::current_y() const { return state_->y; }


QString Sprite::alt_report() const {
    int alt = state_->alt;
    int cfl = is_level() ? alt : state_->cfl;

    alt = (alt + 50) / 100;
    cfl = (cfl + 50) / 100;

    QString dir =   alt <  cfl   ?    "^" :
                    alt == cfl   ?    ">" :
                  /*alt >  cfl*/      "v" ;

    return QString("%1%2%3").arg(alt, 3).arg(dir).arg(cfl, 3);
}

QString Sprite::vel_report() const {
    qreal vel = state_->vel;
    return QString("%1").arg(vel);
}


//
// [protected]
//


void Sprite::focusInEvent(QFocusEvent *event) {
    Q_UNUSED(event);
    setBrush(Qt::black);
}

void Sprite::focusOutEvent(QFocusEvent *event) {
    Q_UNUSED(event);
    setBrush(Qt::yellow);
}

void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    setFocus();
}

void Sprite::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_P: shortRouteProbe(); return;
    case Qt::Key_H: historyTool(); return;
    }
}

void Sprite::shortRouteProbe() {
    if (!short_route_probe_) {
        short_route_probe_ = ShortRouteProbe::create(this);
    } else {
        delete short_route_probe_;
        short_route_probe_ = 0;
    }
}

void Sprite::historyTool() {
    if (!history_tool_)
            history_tool_ = HistoryTool::create(this);
    else {
        delete history_tool_;
        history_tool_ = 0;
    }
}

//
// [private]
//


/**
 * @brief Sprite::advance_position
 * @param ms
 */
void Sprite::advance_position(int ms) {

    state_->vel.set(traits_->current_velocity());

    qreal travel = ms * state_->vel;

    while ( state_->len < travel) {
        travel -= state_->len;
        if (!nextPathPoint()) {
            deactivate();
            return;
        }
    }

    state_->x += travel * (*pathPoint_).dx;
    state_->y += travel * (*pathPoint_).dy;
    state_->len -= travel;

    signaller_.trigger_position_updated();
}

bool Sprite::nextPathPoint() {
    // altitude and velocity only apply first time past for closed paths.
    if (closedPath_) {
        (*pathPoint_).alt = qQNaN();
        (*pathPoint_).vel = qQNaN();
    }

    ++pathPoint_;
    if (pathPoint_ == path_.end()) {
        if (!closedPath_) return false;
        pathPoint_ = path_.begin();
    }
    state_->x = (*pathPoint_).x;
    state_->y = (*pathPoint_).y;
    state_->len = (*pathPoint_).len;
    if (!qIsNaN((*pathPoint_).alt))
            state_->cfl.set((*pathPoint_).alt);
    if (!qIsNaN((*pathPoint_).vel))
            state_->cvl = (*pathPoint_).vel;

    signaller_.trigger_path_updated();

    return true;
}

/**
 * @brief Sprite::deactivate
 */
void Sprite::deactivate() {
    asd()->deactivateAircraft(this);
}


/**
 * @brief Sprite::advance_altitude
 * @param ms
 */
void Sprite::advance_altitude(int ms) {
    if (is_level()) return;

    qreal rateOfClimb = traits_->climb_rate();
    qDebug() << "RateOfClimb: " << rateOfClimb;

    qreal dalt = ms * rateOfClimb;     // @todo: conversion ft/min?
    if (qFabs(state_->cfl - state_->alt) <= qFabs(dalt)) {
        state_->alt.set(state_->cfl);
        reset_level();
        if (level_required()) level_acquired();
    } else {
        state_->alt.set(state_->alt.value() + dalt);
    }

}

bool Sprite::is_level() const { return qIsNaN(state_->cfl); }
void Sprite::reset_level() { state_->cfl.set(qQNaN()); }

bool Sprite::level_required() { return level_required_; }
void Sprite::level_acquired() { level_required_ = false; }


void Sprite::advance_speed(int ms) {
    if (!is_accelerating()) return;

    qreal acceleration = traits_->acceleration();
    qDebug() << "Acceleration: " << acceleration;

    qreal dvel = ms * acceleration;      // @todo: conversion factors?
    if (qFabs(state_->cvl - state_->vel) <= qFabs(dvel)) {
        state_->vel.set(state_->cvl);
        reset_acceleration();
    } else {
        state_->vel.set(state_->vel.value() + dvel);
    }
}

bool Sprite::is_accelerating() { return !qIsNaN(state_->cvl); }
void Sprite::reset_acceleration() { state_->cvl = qQNaN(); }

void Sprite::update_display() {
    setPos(state_->x, state_->y);
    qDebug() << "***** [" << toString() << "] *****";
}

/**
 * @brief Sprite::asd
 * @return
 */
AirSituationDisplay* Sprite::asd() const {
    return qobject_cast<AirSituationDisplay*>(scene());
}

QString Sprite::toString() const {
    return
            QString("%1: (%2,%3) z:%4->%5 v:%6->%7")
                    .arg(callsign_)
                    .arg(state_->x).arg(state_->y)
                    .arg(state_->alt.value()).arg(state_->cfl.value())
                    .arg(state_->vel.value()).arg(state_->cvl)
                ;
}

//------------------------------------------------------------------------------
//
//

Builder::Builder(AircraftSprite::Properties properties) :
        properties_(properties)
{
    reset();
}

Builder* Builder::reset() {
    callsign_ = "";
    type_ = "";
    traits_.reset();
    path_.clear();
    closedPath_ = false;

    return this;
}

Builder* Builder::setCallsign(QString callsign) {
    callsign_ = callsign; return this;
}

Builder* Builder::setAircraftType(QString type) {
    type_ = type; return this;
}

Builder* Builder::setTraits(Traits *traits) {
    traits_.reset(traits);
    traits = 0;             // ScopedPointer takes ownership
    return this;
}

Builder* Builder::addPathPoint(qreal x, qreal y) {
    path_ << Sprite::PathVector(x, y); return this;
}

Builder* Builder::addPathPoint(qreal x, qreal y, qreal alt) {
    path_ << Sprite::PathVector(x, y, alt); return this;
}

Builder* Builder::addPathPoint(qreal x, qreal y, qreal alt, qreal vel) {
    path_ << Sprite::PathVector(x, y, alt, vel); return this;
}

Builder* Builder::addAlitude(qreal alt) {
   path_.last().alt = alt; return this;
}

Builder* Builder::addVelocity(qreal vel) {
   path_.last().vel = vel; return this;
}

Builder* Builder::closePath() {
    closedPath_ = true; return this;
}

Sprite* Builder::build() {
    validate();

    Sprite *aircraft = new Sprite;
    initialise_aircraft(aircraft);
    initialise_traits(aircraft);
    initialise_path(aircraft);
    initialise_state(aircraft);
    initialise_sprite(aircraft);
    create_callout(aircraft);
    aircraft->update_display();
    return aircraft;
}

/**
 * @brief Builder::validate
 * Check that all required parameters are set before proceeding with build. Where
 * possible defaults will be loaded for missing settings, but if no default is
 * available then an exception will be raised.
 */
void Builder::validate() {
    if (traits_.isNull()) throw;
    if (2 > path_.size()) throw;              // exception
}

/**
 * @brief Builder::initialise_aircraft
 * @param sprite
 */
void Builder::initialise_aircraft(Sprite* sprite) {
    sprite->callsign_ = callsign_;
    sprite->type_ = type_;
}

/**
 * @brief Builder::initialise_traits
 * @param s
 */
void Builder::initialise_traits(Sprite *sprite) {
    traits_->attach(sprite);
    sprite->traits_.reset(traits_.take());
}

/**
 * @brief asd::Aircraft::Builder::build_path
 * @param aircraft
 */
void Builder::initialise_path(Sprite *aircraft) {

    QVector<Sprite::PathVector>::iterator it = path_.begin();
    QVector<Sprite::PathVector>::iterator p0 = it;

    if (qIsNaN(p0->alt)) { p0->alt = aircraft->traits_->cruising_altitude(); }
    if (qIsNaN(p0->vel)) { p0->vel = aircraft->traits_->cruising_speed(); }

    while (++it != path_.end()) {
        calculate_path_vector(p0, it);
        p0 = it;
    }

    if (closedPath_) {
        calculate_path_vector(p0, path_.begin());
        aircraft->closedPath_ = true;
    } else {
        path_.removeLast();  // only needed for construction of final vector.
    }

    aircraft->path_ = path_;
    aircraft->pathPoint_ = aircraft->path_.begin();
}

/**
 * @brief asd::Aircraft::Builder::calculate_path_vector
 * @param p0
 * @param p1
 */
void Builder::calculate_path_vector(Sprite::PathVector *p0, const Sprite::PathVector *p1) {
    qreal deltaX = p1->x - p0->x;
    qreal deltaY = p1->y - p0->y;

    p0->len = qSqrt(qPow(deltaX, 2.0) + qPow(deltaY, 2.0));
    p0->dir = qAtan2(deltaY, deltaX);
    p0->dx = qCos(p0->dir);
    p0->dy = qSin(p0->dir);
}

/**
 * @brief Builder::initialise_state
 * @param aircraft
 */
void Builder::initialise_state(Sprite *aircraft) {

    Sprite::State *state = new Sprite::State();

    const Sprite::PathVector &first = aircraft->path_.at(0);
    const Sprite::PathVector &second = aircraft->path_.at(1);

    state->x = first.x;
    state->y = first.y;
    state->alt.set(first.alt);
    state->len = first.len;
    state->vel.set(first.vel);
    state->cfl.set(second.alt);
    state->cvl = second.vel;

    aircraft->state_.reset(state);
}

void Builder::initialise_sprite(Sprite* sprite) {
    sprite->setFlag(QGraphicsItem::ItemIsFocusable);

    sprite->setPen(properties_.outlinePen());
    sprite->setBrush(properties_.brush());
    sprite->setZValue(properties_.layer());

    qreal size = properties_.size();
    sprite->setRect(-size/2, -size/2, size, size);
}

/**
 * @brief Builder::create_callout
 *
 * Create interactive callout block reporting aircraft state within the sprite.
 * A 'callout' line is generated connecting the 'positional indicator' to the
 * 'text block origin'. The 'text block origin' is used to position all the
 * textual information blocks such as 'call block', 'data block', 'altitude
 * block' and 'velocity block'.
 *
 * @param sprite
 */
void Builder::create_callout(Sprite *sprite) {

    QGraphicsLineItem *callout = new QGraphicsLineItem(sprite);
    callout->setPen(properties_.pen());
    QPointF callpt(properties_.callout(), -properties_.callout());
    callout->setLine(QLineF(QPointF(0,0), callpt));

    QGraphicsItem *txtO = new QGraphicsLineItem(0, 0, 0, 0, sprite);
    txtO->moveBy(callpt.x(), callpt.y());

    QFont font = properties_.font();
    QFontMetrics fmtx(font);
    int maxWidth = fmtx.width("W"); // fmtx.maxWidth(); returns 0 on Mac OS X
    int maxHeight = fmtx.height();

    QGraphicsTextItem* calltxt = createTextItem(txtO, 0, 0, font);
    QGraphicsTextItem* datatxt = createTextItem(txtO, 0, maxHeight, font);
    QGraphicsTextItem* alttxt = createTextItem(txtO, 0, 2*maxHeight, font);
    QGraphicsTextItem* veltxt = createTextItem(txtO, 8*maxWidth, 2*maxHeight, font);

    calltxt->setPlainText(callsign_);
    datatxt->setPlainText("Data Block");

    auto setAltitudeText = [=] () { alttxt->setPlainText(sprite->alt_report()); };
    QObject::connect(
            &(sprite->state_->alt),
            &asd::utility::RealNumberObject::valueChanged,
            setAltitudeText
        );
    QObject::connect(
            &(sprite->state_->cfl),
            &asd::utility::RealNumberObject::valueChanged,
            setAltitudeText
        );
    setAltitudeText();


    auto setVelocityText = [=] () { veltxt->setPlainText(sprite->vel_report()); };
    QObject::connect(
            &(sprite->state_->vel),
            &asd::utility::RealNumberObject::valueChanged,
            setVelocityText
        );
    setVelocityText();
}

QGraphicsTextItem* Builder::createTextItem(
        QGraphicsItem* parent, int x, int y, QFont font
) {
    QGraphicsTextItem *item = new QGraphicsTextItem(parent);

    item->setFont(font);
    item->moveBy(x, y);

    return item;
}


} // namespace Aircraft
} // namespace asd
