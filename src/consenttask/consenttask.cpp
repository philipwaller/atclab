#include "consenttask.h"
#include "consenttaskview.h"


ConsentTask::ConsentTask(TaskView *view, const QString &tag)
        : Task(view, tag)
        , text_()
        , acceptMsg_()
        , rejectMsg_()
{
    // validate corrent view type
    consentTaskView();
}

ConsentTaskView* ConsentTask::consentTaskView() {
    auto v = qobject_cast<ConsentTaskView*>(view_);
    if (!v)
            throw;
    return v;
}

void ConsentTask::setAcceptMsg(QString msg) {
    acceptMsg_ = msg;
    auto v = consentTaskView();
    QObject::connect(v, &ConsentTaskView::signal_accepted, [=] () {
            signal_completed( acceptMsg_ );
        });
}

void ConsentTask::setRejectMsg(QString msg) {
    rejectMsg_ = msg;
    auto v = consentTaskView();
    QObject::connect(v, &ConsentTaskView::signal_rejected, [=] () {
            signal_completed( rejectMsg_ );
        });
}

void ConsentTask::initialise() {
    auto view = qobject_cast<ConsentTaskView*>(view_);
    view->setText(text_);
}
