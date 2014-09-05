#include "scale_properties.h"
#include <QSharedData>


class asd::ScaleSprite::PropertiesData : public QSharedData {
public:
    PropertiesData() :
        pen(QPen(Qt::yellow)),
        penMove(QPen(Qt::red)),
        zlayer(0),
        xextent(100), yextent(100),
        xinterval(10), yinterval(10),
        tick(10)
    {}
    PropertiesData(PropertiesData &other) :
        QSharedData(other),
        pen(other.pen),
        penMove(other.penMove),
        zlayer(other.zlayer),
        xextent(other.xextent), yextent(other.yextent),
        xinterval(other.xinterval), yinterval(other.yinterval),
        tick(other.tick)
    {}
    ~PropertiesData() {}

    QPen pen;
    QPen penMove;
    int zlayer;

    int xextent, yextent;
    int xinterval, yinterval;
    int tick;
};


//
//
//

asd::ScaleSprite::Properties::Properties() :
        data_(new asd::ScaleSprite::PropertiesData)
{}

asd::ScaleSprite::Properties::Properties(const asd::ScaleSprite::Properties &rhs) :
        data_(rhs.data_)
{}

asd::ScaleSprite::Properties
&asd::ScaleSprite::Properties::operator=(const asd::ScaleSprite::Properties &rhs)
{
    if (this != &rhs)
        data_.operator=(rhs.data_);
    return *this;
}

asd::ScaleSprite::Properties::~Properties() {}


void asd::ScaleSprite::Properties::setPen(QPen pen) { data_->pen = pen; }
void asd::ScaleSprite::Properties::setPenMove(QPen pen) { data_->penMove = pen; }
void asd::ScaleSprite::Properties::setZlayer(int zlayer) { data_->zlayer = zlayer; }

void asd::ScaleSprite::Properties::setExtents(int extent) { setXextent(extent); setYextent(extent); }
void asd::ScaleSprite::Properties::setXextent(int xextent) { data_->xextent = xextent; }
void asd::ScaleSprite::Properties::setYextent(int yextent) { data_->yextent = yextent; }
void asd::ScaleSprite::Properties::setIntervals(int interval) { setXinterval(interval); setYinterval(interval); }
void asd::ScaleSprite::Properties::setXinterval(int xinterval) { data_->xinterval = xinterval; }
void asd::ScaleSprite::Properties::setYinterval(int yinterval) { data_->yinterval = yinterval; }
void asd::ScaleSprite::Properties::setTick(int tick) { data_->tick = tick; }

QPen asd::ScaleSprite::Properties::pen() { return data_->pen; }
QPen asd::ScaleSprite::Properties::penMove() { return data_->penMove; }
int asd::ScaleSprite::Properties::zlayer() { return data_->zlayer; }

int asd::ScaleSprite::Properties::xextent(){ return data_->xextent; }
int asd::ScaleSprite::Properties::yextent(){ return data_->yextent; }
int asd::ScaleSprite::Properties::xinterval(){ return data_->xinterval; }
int asd::ScaleSprite::Properties::yinterval(){ return data_->yinterval; }
int asd::ScaleSprite::Properties::tick(){ return data_->tick; }
