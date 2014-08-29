#include "task.h"

#include <QAction>
#include <QDebug>
#include <QTimer>

#include "taskview.h"


Task::Task(TaskView *view, const QString &tag)
        : QState(), view_(view), timer_(0), actions_()
{
    setObjectName(tag);
}

void Task::setTimeout(quint32 secs) {
    if (!timer_) {
        timer_ = new QTimer(this);
        timer_->setSingleShot(true);
    }
    timer_->setInterval(secs * 1000);
    QObject::connect(timer_, &QTimer::timeout, this, &Task::signal_terminate);
}

void Task::setShortcut(QKeySequence shortcut) {
    QAction* a = new QAction(this);
    a->setShortcut(shortcut);
    actions_.append(a);
    QObject::connect(a, &QAction::triggered, this, &Task::signal_terminate);
}

TaskView* Task::view() { return view_; }

void Task::begin() {
    initialise();
    initActions();
    initTimers();
    view_->display();
}

void Task::cleanup() {
    if (timer_) timer_->stop();
    view_->removeActions(actions_);
    view_->removeActions();
}

void Task::onEntry(QEvent *event) {
   qDebug() << "IN:>>  State[ " << objectName() << " ]  >>>>>";
   QState::onEntry(event);
   begin();
}

void Task::onExit(QEvent *event) {
   qDebug() << "OUT:<  State[ " << objectName() << " ]  <<<<<";
   QState::onExit(event);
   cleanup();
}

void Task::initActions() {
    view_->addActions(actions_);
}

void Task::initTimers() {
    if (timer_) timer_->start();
}
