#ifndef STRINGTRANSITION_H
#define STRINGTRANSITION_H


#include <QAbstractTransition>
#include <QEvent>


struct StringEvent : public QEvent {
    static const int TYPE;

    StringEvent(const QString &val)
            : QEvent(QEvent::Type(TYPE))
            , value(val)
    {}

    QString value;
};




class StringTransition : public QAbstractTransition {
    Q_OBJECT

public:
    StringTransition(const QString &value) : value_(value) {}

protected:
    virtual bool eventTest(QEvent *e);
    virtual void onTransition(QEvent *) {}

private:
    QString value_;

};



#endif // STRINGTRANSITION_H
