#ifndef REALNUMBEROBJECT_H
#define REALNUMBEROBJECT_H

#include <QObject>
#include <QtNumeric>


namespace asd {
namespace utility {


class RealNumberObject : public QObject
{
    Q_OBJECT
public:
    explicit RealNumberObject(qreal value = qQNaN(), QObject *parent = 0);

    qreal value() const { return value_; }
    operator qreal() const { return value_; }

signals:
    void valueChanged(const qreal newValue);

public slots:
    void set(qreal value);

private:
    qreal value_;
};


}
}

#endif // REALNUMBEROBJECT_H
