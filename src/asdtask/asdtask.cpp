#include "asdtask.h"


#include "asdtaskview.h"


AsdTask::AsdTask(TaskView *view, const QString &tag)
        : Task(view, tag)
{
    auto v = qobject_cast<AsdTaskView*>(view);
    if (!v) throw;
}

void AsdTask::initialise() {
    auto view = qobject_cast<AsdTaskView*>(view_);
}


