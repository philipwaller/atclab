#include "statechart.h"

#include "stringtransition.h"
#include <QDebug>


StateChart::StateChart(const QString& name, QObject *parent)
        : QStateMachine(parent)
{
    setObjectName(name);
}

StateChart::StateChart(QObject *parent)
        : QStateMachine(parent)
{}

void StateChart::postStringEvent(const QString &guard) {
    postEvent(new StringEvent(guard));
}

void StateChart::next() {
    emit signal_next();
}

void StateChart::prev() {
    emit signal_prev();
}



void State::onEntry(QEvent *event) {
   qDebug() << "IN::State::" << objectName() << "::" << event->type();
   QState::onEntry(event);
}

void State::onExit(QEvent *event) {
   qDebug() << "OUT::State::" << objectName() << "::" << event->type();
   QState::onExit(event);
}



void InteruptState::onEntry(QEvent *event) {
   qDebug() << "IN::InteruptState::" << objectName() << "::" << event->type();
   QState::onEntry(event);
}

void InteruptState::onExit(QEvent *event) {
   qDebug() << "OUT::InteruptState::" << objectName() << "::" << event->type();
   QState::onExit(event);
}



void FinalState::onEntry(QEvent *event) {
   qDebug() << "IN::FinalState::" << objectName() << "::" << event->type();
   QFinalState::onEntry(event);
}

void FinalState::onExit(QEvent *event) {
   qDebug() << "OUT::FinalState::" << objectName() << "::" << event->type();
   QFinalState::onExit(event);
}
