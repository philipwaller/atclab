#include "statechart.h"
#include "stringevent.h"


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

