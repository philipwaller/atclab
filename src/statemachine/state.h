#ifndef STATE_H
#define STATE_H

#include <QState>


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


#endif // STATE_H
