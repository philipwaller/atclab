#include "waypoint_properties.h"
#include <QSharedData>


class asd::WaypointSprite::PropertiesData : public QSharedData {
public:
    PropertiesData() :
        pen(QPen(Qt::green, 2)),
        brush(Qt::transparent),
        size(10),
        zlayer(10)
    {}
    PropertiesData(PropertiesData &other) :
        QSharedData(other),
        pen(other.pen),
        brush(other.brush),
        size(other.size),
        zlayer(other.zlayer)
    {}
    ~PropertiesData() {}

    QPen pen;
    QBrush brush;
    qreal size;
    int zlayer;
};


asd::WaypointSprite::Properties::Properties() :
        data_(new asd::WaypointSprite::PropertiesData)
{}

asd::WaypointSprite::Properties::Properties(const asd::WaypointSprite::Properties &rhs) :
        data_(rhs.data_)
{}

asd::WaypointSprite::Properties
&asd::WaypointSprite::Properties::operator=(const asd::WaypointSprite::Properties &rhs)
{
    if (this != &rhs)
        data_.operator=(rhs.data_);
    return *this;
}

asd::WaypointSprite::Properties::~Properties()
{}


void asd::WaypointSprite::Properties::setPen(QPen pen) { data_->pen = pen; }
void asd::WaypointSprite::Properties::setBrush(QBrush brush) { data_->brush = brush; }
void asd::WaypointSprite::Properties::setSize(qreal size) { data_->size = size; }
void asd::WaypointSprite::Properties::setZlayer(int zlayer) { data_->zlayer = zlayer; }

QPen asd::WaypointSprite::Properties::pen() { return data_->pen; }
QBrush asd::WaypointSprite::Properties::brush() { return data_->brush; }
qreal asd::WaypointSprite::Properties::size() { return data_->size; }
int asd::WaypointSprite::Properties::zlayer() { return data_->zlayer; }
