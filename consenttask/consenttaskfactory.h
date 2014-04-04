#ifndef CONSENTTASKFACTORY_H
#define CONSENTTASKFACTORY_H


#include <QObject>
#include <QtPlugin>

#include "itaskfactory.h"


class ConsentTaskFactory : public QObject, ITaskFactory {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "consenttaskplugin.json")
    Q_INTERFACES(ITaskFactory)

public:
    ConsentTaskFactory();

    QString type() const;
    TaskView* createView();
    Task* createTask(TaskView *view, const QString &tag = "");

};


#endif // CONSENTTASKFACTORY_H
