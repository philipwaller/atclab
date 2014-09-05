#ifndef ASDTASK_H
#define ASDTASK_H


#include "task.h"

class AsdTask : public Task {
    Q_OBJECT

    friend class AsdTaskFactory;

private:
    explicit AsdTask(TaskView *view, const QString &tag = "");

    void initialise();

signals:

public slots:

};

#endif // ASDTASK_H
