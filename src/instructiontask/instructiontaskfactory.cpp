#include "instructiontaskfactory.h"

#include "instructiontask.h"
#include "instructiontaskview.h"


InstructionTaskFactory::InstructionTaskFactory() {}


QString InstructionTaskFactory::type() const {
    return "InstructionTask";
}

Task* InstructionTaskFactory::createTask(TaskView *view, const QString &tag) {
    return new InstructionTask(view, tag);
}

TaskView* InstructionTaskFactory::createView() {
    return new InstructionTaskView;
}
