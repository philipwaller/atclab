#ifndef STRINGTRANSITION_H
#define STRINGTRANSITION_H


#include <QAbstractTransition>
#include <QEvent>




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
