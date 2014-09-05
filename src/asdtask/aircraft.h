#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QtNumeric>
#include <QGraphicsEllipseItem>

#include "aircraft_properties.h"
#include "aircraft_traits.h"
#include "airsituationdisplay.h"
#include "realnumberobject.h"

#include <QDebug>

namespace asd {
namespace Aircraft {


class ShortRouteProbe;
class HistoryTool;


/**
 * @brief The SpriteSignaller class
 */
class SpriteSignaller : public QObject {
    Q_OBJECT
public:
    explicit SpriteSignaller(QObject *parent = 0) : QObject(parent) {}

    void trigger_path_updated() { emit path_updated(); }
    void trigger_position_updated() { emit position_updated(); }

signals:
    void path_updated();
    void position_updated();
};


/**
 * @brief The Sprite class
 */
class Sprite : public QGraphicsEllipseItem
{
    friend class Builder;
    friend class Traits;

    struct PathVector;
    struct State;

    enum ControlledState {
        CS_NONE,        // black            >15min from entry
        CS_ANNOUNCED,   // blue             > 2min from entry
        CS_PROPOSED,    // blinking_orange  <2min until entry - can be accepted
        CS_ACCEPTED,    // green            under control in sector
        CS_OVEROUT,     // orange           <2min until exit - can be handed-off
        CS_HANDOFF,     // white            upto 30sec after hand-off
        CS_NOMORE       // black            leaving controlled sector airspace
    };

public:
    void advance(int ms);

    qreal current_speed() const;
    qreal current_deltaX() const;
    qreal current_deltaY() const;

    quint32 current_timetag() const;
    qreal current_x() const;
    qreal current_y() const;

    QString alt_report() const;
    QString vel_report() const;

    const SpriteSignaller* signaller() { return &signaller_; }

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);


    void shortRouteProbe();
    void historyTool();


private:
    explicit Sprite(QGraphicsItem *parent = 0);

    void advance_position(int ms);
    bool nextPathPoint();
    void deactivate();

    void advance_altitude(int ms);
    bool is_level() const;
    void reset_level();

    bool level_required();
    void level_acquired();

    void advance_speed(int ms);
    bool is_accelerating();
    void reset_acceleration();

    void update_display();

    AirSituationDisplay* asd() const;

    QString toString() const;


private:
    QString callsign_;
    QString type_;
    QVector<PathVector> path_;
    QVector<PathVector>::iterator pathPoint_;
    bool closedPath_;
    QScopedPointer<State> state_;
    QScopedPointer<Traits> traits_;
    bool level_required_;

    SpriteSignaller signaller_;

    // Tools
    ShortRouteProbe *short_route_probe_;
    HistoryTool *history_tool_;

};


//
//
//
/**
 * @brief The Sprite::PathVector struct
 *
 * Position, current altitude and velocity, lateral distance, bearing, x and y components.
 */
struct Sprite::PathVector {
    PathVector() {
        x = y = alt = vel = len = dir = dx = dy = qQNaN();
    }
    PathVector(qreal x, qreal y, qreal alt = qQNaN(), qreal vel = qQNaN())
        : x(x), y(y), alt(alt), vel(vel)
        , len(qQNaN()), dir(qQNaN()), dx(qQNaN()), dy(qQNaN())
    {}
    PathVector(const PathVector& rhs)
        : x(rhs.x), y(rhs.y), alt(rhs.alt), vel(rhs.vel)
        , len(rhs.len), dir(rhs.dir), dx(rhs.dx), dy(rhs.dy)
    {}
    QString toString() const{
        return
                QString("[%1, %2, %3, %4, %5, %6, %7, %8]")
                .arg(x).arg(y).arg(alt).arg(vel).arg(len).arg(dir).arg(dx).arg(dy);
    }
    qreal x, y, alt, vel, len, dir, dx, dy;
};


//
//
//

struct Sprite::State {
    State()
            : alt()
            , vel()
            , cfl()
    {
        timetag = 0;
        control = CS_NONE;
        x = y = len = cvl = qQNaN();
    }
    State(const State &rhs)
            : timetag(rhs.timetag)
            , control(rhs.control)
            , x(rhs.x), y(rhs.y)
            , alt(rhs.alt.value())
            , len(rhs.len)
            , vel(rhs.vel.value())
            , cfl(rhs.cfl.value())
            , cvl(rhs.cvl)
    {}
    QString toString() const{
        return
                QString("[x:%1, y:%2, z:%3, l:%4, v:%6, %7]")
                .arg(x).arg(y)
                .arg(qreal(alt))
                .arg(len)
                .arg(qreal(vel))
                .arg(qreal(cfl))
                .arg(cvl);
    }

    quint32 timetag;                        // time tag (from when?)
    ControlledState control;                // current controller status
    qreal x, y;                             // lateral grid position - meters north/east
    asd::utility::RealNumberObject alt;     // altitude - feet?
    qreal len;                              // length to next path point
    asd::utility::RealNumberObject vel;     // speed - airspeed/groundspeed?
    asd::utility::RealNumberObject cfl;     // cleared flight level
    qreal cvl;                              // cleared(?) velocity

};


//
//
//

class Builder {
public:
    explicit Builder(AircraftSprite::Properties properties);

    Builder* reset();

    Builder* setCallsign(QString callsign);
    Builder* setAircraftType(QString type);
    Builder* setTraits(Traits* traits);

    Builder* addPathPoint(qreal x, qreal y);
    Builder* addPathPoint(qreal x, qreal y, qreal alt);
    Builder* addPathPoint(qreal x, qreal y, qreal alt, qreal vel);
    Builder* addAlitude(qreal alt);
    Builder* addVelocity(qreal vel);
    Builder* closePath();

    Sprite* build();

private:
    void validate();
    void initialise_aircraft(Sprite* sprite);
    void initialise_traits(Sprite *sprite);
    void initialise_path(Sprite *aircraft);
    void calculate_path_vector(
            Sprite::PathVector *p0, const Sprite::PathVector *p1
        );
    void initialise_state(Sprite *aircraft);
    void initialise_sprite(Sprite *sprite);
    void create_callout(Sprite* sprite);
    QGraphicsTextItem* createTextItem(
            QGraphicsItem *parent, int x, int y, QFont font
        );

private:
    AircraftSprite::Properties properties_;
    QString callsign_;
    QString type_;
    QScopedPointer<Traits> traits_;
    QVector<Sprite::PathVector> path_;
    bool closedPath_;
};


} // namespace Aircraft
} // namespace asd

#endif // AIRCRAFT_H
