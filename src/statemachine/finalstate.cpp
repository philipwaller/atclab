#include "finalstate.h"

#include <QDebug>
#include <QEvent>


void FinalState::onEntry(QEvent *event) {
   qDebug() << "IN::FinalState::" << objectName() << "::" << event->type();
   QFinalState::onEntry(event);
}

void FinalState::onExit(QEvent *event) {
   qDebug() << "OUT::FinalState::" << objectName() << "::" << event->type();
   QFinalState::onExit(event);
}
