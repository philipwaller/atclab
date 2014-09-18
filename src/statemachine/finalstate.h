#ifndef FINALSTATE_H
#define FINALSTATE_H


#include <QFinalState>


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



#endif // FINALSTATE_H
