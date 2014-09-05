#ifndef AIRSITUATIONDISPLAY_H
#define AIRSITUATIONDISPLAY_H


#include <QObject>
#include <QGraphicsScene>
#include <QQueue>
#include <QList>


namespace asd {

namespace Aircraft {
    class Sprite;
}



//class AirSituationDisplay : public QObject
class AirSituationDisplay : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit AirSituationDisplay(QObject * parent = 0);
    ~AirSituationDisplay() {}

    QWidget* view();
    int updateInterval();
    void deactivateAircraft(Aircraft::Sprite *aircraft);

public slots:
    void start();
    void advance();

private:
    QList<Aircraft::Sprite*> aircraft_;
    QList<Aircraft::Sprite*> deactivatedAircraft_;
    QTimer *advanceTimer_;

public:

    class Builder {
    public:
        explicit Builder();
        ~Builder();

        Builder* setSceneRect(qreal x, qreal y, qreal w, qreal h);
        Builder* addItem(QGraphicsItem *item);
        Builder* setAdvance(int msec);

        AirSituationDisplay* build();

    private:
        QRect sceneRect_;
        QQueue<QGraphicsItem*> items_;
        int advance_;

    }; // class Builder

};

} // namespace asd

#endif // AIRSITUATIONDISPLAY_H
