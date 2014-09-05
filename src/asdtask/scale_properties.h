#ifndef SCALE_PROPERTIES_H
#define SCALE_PROPERTIES_H


#include <QExplicitlySharedDataPointer>
#include <QPen>


namespace asd {
namespace ScaleSprite {


class PropertiesData;

class Properties
{
public:
    Properties();
    Properties(const Properties &);
    Properties &operator=(const Properties &);
    ~Properties();

    void setPen(QPen pen);
    void setPenMove(QPen pen);
    void setZlayer(int zlayer);
    void setExtents(int extent);
    void setXextent(int xextent);
    void setYextent(int yextent);
    void setIntervals(int interval);
    void setXinterval(int xinterval);
    void setYinterval(int yinterval);
    void setTick(int tick);

    QPen pen();
    QPen penMove();
    int zlayer();
    int xextent();
    int yextent();
    int xinterval();
    int yinterval();
    int tick();

private:
    QExplicitlySharedDataPointer<PropertiesData> data_;
};


} // namespace ScaleSprite
} // namespace asd


#endif // SCALE_PROPERTIES_H
