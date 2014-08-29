#ifndef STATECHARTBUILDER_H
#define STATECHARTBUILDER_H


#include <QString>

#include "statechart.h"

class QState;
class QAbstractTransition;

class Task;


class StateChartBuilder
{
public:
    explicit StateChartBuilder(StateChart& stateChart);
    
    void addStateChartNext(QObject *sender, const QByteArray signal);
    void addStateChartPrev(QObject *sender, const QByteArray signal);
    void addStateChartStart(QObject *sender, const QByteArray signal);
    void addStateChartPause(QObject *sender, const QByteArray signal);
    void addStateChartResume(QObject *sender, const QByteArray signal);
    void addStateChartExit(QObject *sender, const QByteArray signal);

    void startPhase(const QString& name);
    void endPhase();
    void addTask(Task *task);
    void addGuardedTransition(
            Task *task, const QString &guard, const QString &target
        );

    StateChart& build();


private:
    void setInitialStates(QState* state);
    void addTransitions(QState* state);
    void initGuardedTransitions();


private:
    StateChart &chart_;
    State *experiment_;
    InteruptState *interupted_;
    FinalState *final_;
    QState *currentParent_;
    QMap<QString, Task*> namedStates_;
    QList<QPair< QAbstractTransition*, QString> > transitionTargets_;


};


#endif // STATECHARTBUILDER_H
