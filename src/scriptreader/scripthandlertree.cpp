#include "scripthandlertree.h"

#include "scripthandler.h"



///////////////////////////////////////////////////////////////////////////////
// [class] ScriptHandlerTree
//

ScriptHandlerTree::ScriptHandlerTree(QObject *parent) :
        QObject(parent) ,
        root_()
{

}

ScriptHandlerNode* ScriptHandlerTree::addChild(ScriptHandler *handler, ScriptHandlerNode *parent) {
    ScriptHandlerNode *node = new ScriptHandlerNode(handler, this);
    node->setParentNode(parent);
    return node;
}


///////////////////////////////////////////////////////////////////////////////
// ScriptHandlerNode
//

ScriptHandlerNode::ScriptHandlerNode(ScriptHandler *handler, QObject *parent)
        : QObject(parent)
        , handler_(handler)
{

}
