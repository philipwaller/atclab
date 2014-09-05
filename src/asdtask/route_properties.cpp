#include "route_properties.h"
#include <QSharedData>


class asd::RouteSprite::PropertiesData : public QSharedData
{
    public:
    PropertiesData() :
            pen(QPen(QBrush(Qt::black), 5)),
            zlayer(10)
    {}
    PropertiesData(PropertiesData &other) :
            QSharedData(other),
            pen(other.pen),
            zlayer(other.zlayer)
    {}
    ~PropertiesData() {}

    QPen pen;
    int zlayer;
};

//
//
//

asd::RouteSprite::Properties::Properties() :
        data_(new asd::RouteSprite::PropertiesData)
{}

asd::RouteSprite::Properties::Properties(const asd::RouteSprite::Properties &rhs) :
        data_(rhs.data_)
{}

asd::RouteSprite::Properties
&asd::RouteSprite::Properties::operator=(const asd::RouteSprite::Properties &rhs)
{
    if (this != &rhs)
        data_.operator=(rhs.data_);
    return *this;
}

void asd::RouteSprite::Properties::setPen(QPen pen) { data_->pen = pen; }
void asd::RouteSprite::Properties::setZlayer(int zlayer) {data_->zlayer = zlayer; }

QPen asd::RouteSprite::Properties::pen() { return data_->pen; }
int asd::RouteSprite::Properties::zlayer() { return data_->zlayer; }


asd::RouteSprite::Properties::~Properties() {}
