#ifndef STRINGEVENT_H
#define STRINGEVENT_H

#include <QEvent>
#include <QString>


//! A StringEvent class contains parameters that describe a string event.
/*!
  String events are used in by StateCharts for conditional transitions that are
  controlled by a QString identifier (StringTransition).
 */
struct StringEvent : public QEvent {
    static const int TYPE;

    StringEvent(const QString &val)
            : QEvent(QEvent::Type(TYPE))
            , value(val)
    {}

    QString value;
};


#endif // STRINGEVENT_H
