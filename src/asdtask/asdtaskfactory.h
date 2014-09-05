#ifndef ASDTASKFACTORY_H
#define ASDTASKFACTORY_H


#include <QObject>
#include <QtPlugin>

#include "itaskfactory.h"


class AsdTaskFactory : public QObject, ITaskFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "asdtaskplugin.json")
    Q_INTERFACES(ITaskFactory)

public:
    explicit AsdTaskFactory();

    QString type() const;
    TaskView* createView();
    Task* createTask(TaskView *view, const QString &tag = "");

};


#endif // ASDTASKFACTORY_H
