#include "state.h"

#include <QDebug>
#include <QEvent>


void State::onEntry(QEvent *event) {
   qDebug() << "IN::State::" << objectName() << "::" << event->type();
   QState::onEntry(event);
}

void State::onExit(QEvent *event) {
   qDebug() << "OUT::State::" << objectName() << "::" << event->type();
   QState::onExit(event);
}

