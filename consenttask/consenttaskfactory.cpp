#include "consenttaskfactory.h"

#include "consenttask.h"
#include "consenttaskview.h"


ConsentTaskFactory::ConsentTaskFactory() {}


QString ConsentTaskFactory::type() const {
    return "ConsentTask";
}

TaskView* ConsentTaskFactory::createView() {
    return new ConsentTaskView;
}

Task* ConsentTaskFactory::createTask(TaskView *view, const QString &tag) {
    return new ConsentTask(view, tag);
}
