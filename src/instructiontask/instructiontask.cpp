#include "instructiontask.h"


#include "instructiontaskview.h"



InstructionTask::InstructionTask(TaskView *view, const QString &tag)
    : Task(view, tag)
    , text_()
{
    auto v = qobject_cast<InstructionTaskView*>(view);
    if (!v) throw;
}


void InstructionTask::initialise() {
    auto view = qobject_cast<InstructionTaskView*>(view_);
    view->setText(text_);
}
