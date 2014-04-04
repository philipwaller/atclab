#ifndef CONSENTTASK_H
#define CONSENTTASK_H


#include "task.h"

class ConsentTaskView;

class ConsentTask : public Task {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString acceptMsg MEMBER acceptMsg_ WRITE setAcceptMsg)
    Q_PROPERTY(QString rejectMsg MEMBER rejectMsg_ WRITE setRejectMsg)

    friend class ConsentTaskFactory;


private:
    explicit ConsentTask(TaskView *view, const QString &tag = "");


public:
    ConsentTaskView* consentTaskView();

    QString text() { return text_; }
    QString rejectMsg() { return rejectMsg_; }
    void setText(QString text) { text_ = text; }
    void setAcceptMsg(QString msg);
    void setRejectMsg(QString msg);

private:
    void initialise();


private:
    QString text_;
    QString acceptMsg_;
    QString rejectMsg_;


};

#endif // CONSENTTASK_H
