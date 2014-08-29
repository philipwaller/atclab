#ifndef SCRIPTHANDLERTREE_H
#define SCRIPTHANDLERTREE_H

#include <QObject>


class ScriptHandler;
class ScriptHandlerNode;


class ScriptHandlerTree : public QObject
{
    Q_OBJECT
public:
    explicit ScriptHandlerTree(QObject *parent = 0);

    ScriptHandlerNode* addChild(ScriptHandler *handler, ScriptHandlerNode *parent);
    ScriptHandlerNode* addChoice(ScriptHandler *handler, ScriptHandlerNode *parent);

    ScriptHandler* getHandler(const QStringRef);

signals:

public slots:

private:
    ScriptHandlerNode* root_;
    ScriptHandlerNode* current_;

};


// TODO:
// choice node
// sequence node

//!
/*!
 * \brief The ScriptHandlerNode class
 *
 * Holds a reference to ScriptHandler and is used in the construction of a ScriptHandlerTree.
 * Each node references its parent node and child nodes. Each node maybe optional or used upto
 * a finite number of times, depending upon the values assigned to the variables minOccurs and
 * maxOccurs.
 *
 * The ScriptHandlerNode is a base class and is inherited by Choice & Sequence.
 */
class ScriptHandlerNode : public QObject
{
    Q_OBJECT
public:
    explicit ScriptHandlerNode(ScriptHandler* handler, QObject *parent = 0);

    void setParentNode(ScriptHandlerNode* node) { parentNode_ = node; }
    void setMinOccurs(int minOccurs) { minOccurs_ = minOccurs; }
    void setMaxOccurs(int maxOccurs) { maxOccurs_ = maxOccurs; }

signals:

public slots:

private:
    ScriptHandler *handler_;
    ScriptHandlerNode *parentNode_;
    int minOccurs_;
    int maxOccurs_;
    QList<ScriptHandlerNode*> children_;

};

#endif // SCRIPTHANDLERTREE_H
