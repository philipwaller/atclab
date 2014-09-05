#include "sector_properties.h"
#include <QSharedData>

class asd::SectorSprite::PropertiesData : public QSharedData {
public:
    PropertiesData() :
        pen(QPen(QBrush(Qt::darkGreen), 10)),
        brush(QBrush(Qt::gray)),
        activeBrush(QBrush(Qt::blue)),
        zlayer(-1)
    {}
    PropertiesData(PropertiesData &other) :
        QSharedData(other),
        pen(other.pen),
        brush(other.brush),
        activeBrush(other.activeBrush),
        zlayer(other.zlayer)
    {}
    ~PropertiesData() {}

    QPen pen;
    QBrush brush;
    QBrush activeBrush;
    int zlayer;
};


//
//
//

asd::SectorSprite::Properties::Properties() :
        data_(new asd::SectorSprite::PropertiesData)
{}

asd::SectorSprite::Properties::Properties(const Properties &rhs) :
        data_(rhs.data_)
{}

asd::SectorSprite::Properties
&asd::SectorSprite::Properties::operator=(const asd::SectorSprite::Properties &rhs)
{
    if (this != &rhs)
        data_.operator=(rhs.data_);
    return *this;
}

asd::SectorSprite::Properties::~Properties() {}


void asd::SectorSprite::Properties::setPen(QPen pen) { data_->pen = pen; }
void asd::SectorSprite::Properties::setBrush(QBrush brush) { data_->brush = brush; }
void asd::SectorSprite::Properties::setActiveBrush(QBrush brush) { data_->brush = brush; }
void asd::SectorSprite::Properties::setZlayer(int zlayer) { data_->zlayer = zlayer; }

QPen asd::SectorSprite::Properties::pen() { return data_->pen; }
QBrush asd::SectorSprite::Properties::brush() { return data_->brush; }
QBrush asd::SectorSprite::Properties::activeBrush() { return data_->activeBrush; }
int asd::SectorSprite::Properties::zlayer() { return data_->zlayer; }




