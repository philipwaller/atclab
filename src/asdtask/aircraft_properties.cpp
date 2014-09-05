#include "aircraft_properties.h"
#include <QSharedData>


class asd::AircraftSprite::PropertiesData : public QSharedData
{
    public:
    PropertiesData() :
            font("Courier", 15),
            outlinePen(Qt::NoPen),
            brush(Qt::darkGreen),
            size(10),
            layer(100),
            callout(50),
            pen(QPen(Qt::darkGreen))
    {}
    PropertiesData(PropertiesData &other) :
            QSharedData(other),
            font(other.font),
            outlinePen(other.outlinePen),
            brush(other.brush),
            size(other.size),
            layer(other.layer),
            callout(other.callout),
            pen(other.pen)
    {}
    ~PropertiesData() {}

    QFont font;
    QPen outlinePen;
    QBrush brush;
    qreal size;
    int layer;
    int callout;
    QPen pen;

};


asd::AircraftSprite::Properties::Properties()
    : data_(new asd::AircraftSprite::PropertiesData)
{}

asd::AircraftSprite::Properties::Properties(const asd::AircraftSprite::Properties &rhs)
    : data_(rhs.data_)
{}

asd::AircraftSprite::Properties
&asd::AircraftSprite::Properties::operator=(const AircraftSprite::Properties &rhs)
{
    if (this != &rhs)
        data_.operator=(rhs.data_);
    return *this;
}

void asd::AircraftSprite::Properties::setFont(QFont font) { data_->font = font; }
void asd::AircraftSprite::Properties::setOutlinePen(QPen pen) { data_->outlinePen = pen; }
void asd::AircraftSprite::Properties::setBrush(QBrush brush) { data_->brush = brush; }
void asd::AircraftSprite::Properties::setSize(qreal size) { data_->size = size; }
void asd::AircraftSprite::Properties::setLayer(int layer) { data_->layer = layer; }
void asd::AircraftSprite::Properties::setCallout(int callout) { data_->callout = callout; }
void asd::AircraftSprite::Properties::setPen(QPen pen) { data_->pen = pen; }

QFont asd::AircraftSprite::Properties::font() { return data_->font; }
QPen asd::AircraftSprite::Properties::outlinePen() { return data_->outlinePen; }
QBrush asd::AircraftSprite::Properties::brush() { return data_->brush; }
qreal asd::AircraftSprite::Properties::size() { return data_->size; }
int asd::AircraftSprite::Properties::layer() { return data_->layer; }
int asd::AircraftSprite::Properties::callout() { return data_->callout; }
QPen asd::AircraftSprite::Properties::pen() { return data_->pen; }


asd::AircraftSprite::Properties::~Properties()
{}
