#ifndef INTERUPTSTATE_H
#define INTERUPTSTATE_H


#include <QState>


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


#endif // INTERUPTSTATE_H
