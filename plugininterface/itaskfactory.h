#ifndef ITASKFACTORY_H
#define ITASKFACTORY_H


#include <QString>


class Task;
class TaskView;


class ITaskFactory {

public:
    virtual ~ITaskFactory() {}
    virtual QString type() const = 0;

    virtual TaskView* createView() = 0;
    virtual Task* createTask(TaskView *view, const QString &tag = "") = 0;

};


#define Plugin_iid "org.atclab.PluginManager.ITaskFactory"
Q_DECLARE_INTERFACE(ITaskFactory, Plugin_iid)



#endif // ITASKFACTORY_H
