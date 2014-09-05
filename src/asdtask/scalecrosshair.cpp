#include "scalecrosshair.h"

#include <QApplication>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QPen>


//------------------------------------------------------------------------------
//
//

asd::ScaleCrossHair::ScaleCrossHair(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    setCursor(QCursor(Qt::OpenHandCursor));
    setAcceptedMouseButtons(Qt::LeftButton);
}

void asd::ScaleCrossHair::setPen(const QPen &pen) {
    foreach (QGraphicsItem *child, childItems()) {
        QGraphicsLineItem *line = qgraphicsitem_cast<QGraphicsLineItem*>(child);
        if (line) line->setPen(pen);
    }
}

QRectF asd::ScaleCrossHair::boundingRect() const {
    return childrenBoundingRect();
}

void asd::ScaleCrossHair::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QList<QGraphicsItem*> children = childItems();
    foreach (QGraphicsItem *child, children)
            child->paint(painter, option, widget);
}


void asd::ScaleCrossHair::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    setCursor(Qt::ClosedHandCursor);
    setPen(dragPen_);
}

void asd::ScaleCrossHair::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
            return;
    QPointF offset = event->scenePos() - event->lastScenePos();
    this->moveBy(offset.rx(), offset.ry());
}

void asd::ScaleCrossHair::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event)
    setCursor(Qt::OpenHandCursor);
    setPen(pen_);
}

//------------------------------------------------------------------------------
//
//

asd::ScaleCrossHair::Builder::Builder(asd::ScaleSprite::Properties propterties) :
        properties_(propterties)
{}

asd::ScaleCrossHair* asd::ScaleCrossHair::Builder::build() {
    asd::ScaleCrossHair *scale = new asd::ScaleCrossHair;

    int xe = properties_.xextent();
    int ye = properties_.yextent();
    int xi = properties_.xinterval();
    int yi = properties_.yinterval();
    int tk = properties_.tick();

    // X-hair

    new QGraphicsLineItem(-xe, 0, xe, 0, scale);
    new QGraphicsLineItem(0, -ye, 0, ye, scale);

    int tick;
    for (int i = xi, n = 1; i <= xe; i += xi, ++n) {
        tick = tk;
        if (!(n % 5)) tick *= 2;
        if (!(n % 10)) tick *= 2;
        new QGraphicsLineItem(i, -tick, i, tick, scale);
        new QGraphicsLineItem(-i, -tick, -i, tick, scale);
    }
    for (int j = yi, m = 1; j <= ye; j += yi, ++m) {
        tick = tk;
        if (!(m % 5)) tick *= 2;
        if (!(m % 10)) tick *= 2;
        new QGraphicsLineItem(-tick, j, tick, j, scale);
        new QGraphicsLineItem(-tick, -j, tick, -j, scale);
    }

    scale->pen_ = properties_.pen();
    scale->dragPen_ = properties_.penMove();

    scale->setPen(scale->pen_);

    return scale;
};

