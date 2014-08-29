#ifndef SCRIPTHANDLERTREEBUILDER_H
#define SCRIPTHANDLERTREEBUILDER_H

#include <QObject>

class ScriptHandlerTree;


class ScriptHandlerTreeBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ScriptHandlerTreeBuilder(ScriptHandlerTree &tree, QObject *parent = 0);

signals:

public slots:

private:
    ScriptHandlerTree &tree_;

};

#endif // SCRIPTHANDLERTREEBUILDER_H
