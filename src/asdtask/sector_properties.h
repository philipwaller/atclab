#ifndef SECTOR_PROPERTIES_H
#define SECTOR_PROPERTIES_H


#include <QPen>
#include <QExplicitlySharedDataPointer>


namespace asd {
namespace SectorSprite {


class PropertiesData;


class Properties
{
public:
    Properties();
    Properties(const Properties &);
    Properties &operator=(const Properties &);
    ~Properties();

    void setPen(QPen pen);
    void setBrush(QBrush brush);
    void setActiveBrush(QBrush brush);
    void setZlayer(int zlayer);

    QPen pen();
    QBrush brush();
    QBrush activeBrush();
    int zlayer();

private:
    QExplicitlySharedDataPointer<PropertiesData> data_;
};


} // namespace SectorSprite
} // namespace asd


#endif // SECTOR_PROPERTIES_H
