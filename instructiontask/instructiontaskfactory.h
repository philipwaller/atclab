#ifndef INSTRUCTIONTASKFACTORY_H
#define INSTRUCTIONTASKFACTORY_H


#include <QObject>
#include <QtPlugin>

#include "itaskfactory.h"


/**
 * @brief The InstructionTaskFactory class
 */
class InstructionTaskFactory : public QObject, ITaskFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "instructiontaskplugin.json")
    Q_INTERFACES(ITaskFactory)

public:
    InstructionTaskFactory();

    QString type() const;
    TaskView* createView();
    Task* createTask(TaskView *view, const QString &tag = "");
};


#endif // INSTRUCTIONTASKFACTORY_H
