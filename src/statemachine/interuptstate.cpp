#include "interuptstate.h"

#include <QDebug>
#include <QEvent>


void InteruptState::onEntry(QEvent *event) {
   qDebug() << "IN::InteruptState::" << objectName() << "::" << event->type();
   QState::onEntry(event);
}

void InteruptState::onExit(QEvent *event) {
   qDebug() << "OUT::InteruptState::" << objectName() << "::" << event->type();
   QState::onExit(event);
}

