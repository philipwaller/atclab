#ifndef STATECHART_H
#define STATECHART_H


#include <QStateMachine>

//! The StateChart class provides a hierachical finite state machine.
/*!
  The StateChart is a state machine that manages a set of States and the
  transitions between those states;
 */
class StateChart : public QStateMachine {
        Q_OBJECT

public:
        explicit StateChart(const QString& name, QObject *parent = 0);
        explicit StateChart(QObject *parent = 0);

public slots:
        void postStringEvent(const QString &guard);

        void next();
        void prev();

signals:
        void signal_next();
        void signal_prev();

};




#endif // STATECHART_H
