#include "realnumberobject.h"

asd::utility::RealNumberObject::RealNumberObject(qreal value, QObject *parent)
        : QObject(parent)
        , value_(value)
{}

void asd::utility::RealNumberObject::set(qreal value) {
    value_ = value;
    emit valueChanged(value_);
}
