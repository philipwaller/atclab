#include "scripthandlertreebuilder.h"

ScriptHandlerTreeBuilder::ScriptHandlerTreeBuilder(ScriptHandlerTree &tree, QObject *parent)
        : QObject(parent)
        , tree_(tree)
{
}
