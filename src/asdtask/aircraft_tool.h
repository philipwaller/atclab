#ifndef AIRCRAFT_TOOL_H
#define AIRCRAFT_TOOL_H


#include <QObject>
#include <QListIterator>
#include <QGraphicsEllipseItem>


class QGraphicsLineItem;

namespace asd {
namespace Aircraft {


class Sprite;


/**
 * @brief The Tool class
 */
class Tool : public QObject
{
    Q_OBJECT
public:
    explicit Tool(Sprite* aircraft, QObject *parent = 0);
    virtual ~Tool();

signals:

public slots:
    virtual void update() = 0;

protected:
    Sprite *aircraft_;

};


/**
 * @brief The ShortRouteProbe class
 */
class ShortRouteProbe : public Tool
{
    Q_OBJECT
private:
    explicit ShortRouteProbe(Sprite *aircraft, QObject *parent = 0);

public:
    static ShortRouteProbe* create(Sprite *aircraft);
    ~ShortRouteProbe();

public slots:
    void update();

private:
    QGraphicsLineItem *probe_;


};


/**
 * @brief The HistoryTool class
 */
class HistoryTool : public Tool
{
    Q_OBJECT
private:
    explicit HistoryTool(Sprite *aircraft, QObject *parent = 0);

public:
    static HistoryTool* create(Sprite *aircraft);
    ~HistoryTool();

public slots:
    void update();

private:
    void createPoint();

private:
    QList<QGraphicsEllipseItem*> dots_;
};



} // namespace Aircraft
} // namespace asd



#endif // AIRCRAFT_TOOL_H
