#include "statechartbuilder.h"

#include <QDebug>

#include "stringtransition.h"
#include "task.h"


StateChartBuilder::StateChartBuilder(StateChart &stateChart)
        : chart_(stateChart)
        , experiment_(new State(QString("Experiment"), &chart_))
        , interupted_(new InteruptState(QString("TopInterupt"), &chart_))
        , final_(new FinalState(QString("TopFinal"), &chart_))
        , currentParent_(&chart_)
        , namedStates_()
        , transitionTargets_()
{
    currentParent_ = experiment_;
}

void StateChartBuilder::addStateChartNext(QObject *sender, const QByteArray signal) {
    QObject::connect(sender, signal, &chart_, SLOT(next()));
}

void StateChartBuilder::addStateChartPrev(QObject *sender, const QByteArray signal) {
    QObject::connect(sender, signal, &chart_, SLOT(prev()));
}

void StateChartBuilder::addStateChartStart(QObject *sender, const QByteArray signal) {
    interupted_->addTransition(sender, signal, experiment_);
}

void StateChartBuilder::addStateChartPause(QObject *sender, const QByteArray signal) {
    experiment_->addTransition(sender, signal, interupted_);
}

void StateChartBuilder::addStateChartResume(QObject *sender, const QByteArray signal) {
    // @todo: transition to QHistoryState
    Q_UNUSED(sender)
    Q_UNUSED(signal)
}

void StateChartBuilder::addStateChartExit(QObject *sender, const QByteArray signal) {
    qDebug() << "Add StateChart::exit()[ "
             << sender->metaObject()->className()
             << ", " << signal << " ]";
    experiment_->addTransition(sender, signal, final_);
    interupted_->addTransition(sender, signal, final_);
}


void StateChartBuilder::startPhase(const QString& name) {
    State* phase = new State(name, currentParent_);
    currentParent_ = phase;
    QObject::connect(phase, &State::finished, &chart_, &StateChart::next);
}

void StateChartBuilder::endPhase() {
    FinalState *final = new FinalState(QString("FinalInPhase"), currentParent_);
    Q_UNUSED(final);

    currentParent_ = currentParent_->parentState();
}

/**
 * @brief StateChartBuilder::addTask
 * @param task
 * @param name
 */
void StateChartBuilder::addTask(Task *task) {
    task->setParent(currentParent_);
    QObject::connect(
            task, &Task::signal_terminate, &chart_, &StateChart::next
        );
    QObject::connect(
            task, &Task::signal_completed, &chart_, &StateChart::postStringEvent
        );
    if (!task->objectName().isEmpty())
            namedStates_.insert(task->objectName(), task);
}

/**
 * @brief StateChartBuilder::addGuardedTransition
 * @param task
 * @param guard
 * @param target
 */
void StateChartBuilder::addGuardedTransition(
        Task *task, const QString &guard, const QString &target
) {
    StringTransition *t = new StringTransition(guard);
    task->addTransition(t);
    transitionTargets_ << qMakePair(t, target);
}

StateChart& StateChartBuilder::build() {

    // Check that composite States have been terminated
    while (currentParent_ !=  &chart_) {
        endPhase();
    }

    setInitialStates(&chart_);
    addTransitions(experiment_);
    initGuardedTransitions();

    return chart_;
}

void StateChartBuilder::setInitialStates(QState* state) {
    QList<QState*> childStates
            = state->findChildren<QState*>(QString(), Qt::FindDirectChildrenOnly);
    if (childStates.isEmpty()) return;

    qDebug() << "Set Initial State:: "
             <<  state->objectName() << " <-- " << childStates.first()->objectName();
    state->setInitialState(childStates.first());
    for (int i = 0; i < childStates.size(); ++i) {
        setInitialStates(childStates.at(i));
    }
}

void StateChartBuilder::addTransitions(QState* state) {
    QList<QAbstractState*> childStates
            = state->findChildren<QAbstractState*>(QString(), Qt::FindDirectChildrenOnly);
    if (childStates.isEmpty()) return;

    for (QList<QAbstractState*>::iterator it = childStates.begin(); ; ) {
        QState* sourceState = qobject_cast<QState*>(*it);
        ++it;
        if (it == childStates.end()) break;
        qDebug() << "Transition:: "
                 << sourceState->objectName() << " --> " << (*it)->objectName();
        sourceState->addTransition(&chart_, SIGNAL(signal_next()), *it);
        addTransitions(sourceState);
    }
}

void StateChartBuilder::initGuardedTransitions() {
   for (int i = 0; i < transitionTargets_.size(); ++i) {
       QPair<QAbstractTransition*, QString> p = transitionTargets_.at(i);
       if (!namedStates_.contains(p.second))
                throw;
       p.first->setTargetState(namedStates_.value(p.second));
   }
}
