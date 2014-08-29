#ifndef TASK_H
#define TASK_H


#include <QState>
#include <QList>

class QAction;
class QTimer;

class StringTransition;
class TaskView;


class Task : public QState{
    Q_OBJECT

public:
    explicit Task(TaskView *view, const QString &tag = "");

    void setTimeout(quint32 secs);
    void setShortcut(QKeySequence shortcut);

    TaskView* view();

    void begin();
    void cleanup();

signals:
    // @todo: do we need two signals?
    void signal_completed(QString);
    void signal_terminate();

protected:
    virtual void initialise() = 0;

    virtual void onEntry(QEvent *);
    virtual void onExit(QEvent *);

private:
    void initActions();
    void initTimers();

protected:
    TaskView *view_;
    QTimer *timer_;
    QList<QAction *> actions_;

};


#endif // TASK_H
