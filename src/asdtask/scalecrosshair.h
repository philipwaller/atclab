#ifndef SCALECROSSHAIR_H
#define SCALECROSSHAIR_H


#include <QGraphicsItem>

#include "scale_properties.h"


namespace asd {


class ScaleCrossHair : public QGraphicsItem
{
private:
    explicit ScaleCrossHair(QGraphicsItem *parent = 0);
    
public:
    void setPen(const QPen &pen);

public: // pure virtual
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected: // virtual
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QPen pen_;
    QPen dragPen_;


public:
    class Builder {
    public:
        Builder(asd::ScaleSprite::Properties propterties);

        ScaleCrossHair* build();

    private:
        ScaleSprite::Properties properties_;

    };
    
};

} // namespace asd

#endif // SCALECROSSHAIR_H
