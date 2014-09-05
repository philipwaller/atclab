#include "asdtaskfactory.h"

#include "asdtask.h"
#include "asdtaskview.h"


AsdTaskFactory::AsdTaskFactory() {}


QString AsdTaskFactory::type() const {
    return "AsdTask";
}

TaskView* AsdTaskFactory::createView() {
    return new AsdTaskView;
}

Task* AsdTaskFactory::createTask(TaskView *view, const QString &tag) {
    return new AsdTask(view, tag);
}
