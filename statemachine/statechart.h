#ifndef STATECHART_H
#define STATECHART_H


#include <QObject>
#include <QFinalState>
#include <QStateMachine>


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



class State : public QState {
    Q_OBJECT

public:
    explicit State(const QString &tag, QState *parent = 0)
        : QState(parent) { setObjectName(tag); }
    virtual ~State() {}

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);

};



class InteruptState : public QState {
    Q_OBJECT

public:
    explicit InteruptState(const QString &tag, QState *parent = 0)
        : QState(parent) { setObjectName(tag); }
    virtual ~InteruptState() {}

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);

};



class FinalState : public QFinalState {
    Q_OBJECT

public:
    explicit FinalState(const QString& tag, QState *parent = 0)
        : QFinalState(parent) { setObjectName(tag); }
    virtual ~FinalState() {}

protected:
    void onEntry(QEvent *event);
    void onExit(QEvent *event);

};



#endif // STATECHART_H
