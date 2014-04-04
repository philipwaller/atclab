#ifndef TASKVIEW_H
#define TASKVIEW_H


#include <QObject>
#include <QWidget>
#include <QStackedWidget>


class TaskView : public QWidget {
    Q_OBJECT

public:
    explicit TaskView();

public:
    void removeActions();
    void removeActions(QList<QAction *> actions);
    void display();


};


#endif // TASKVIEW_H
