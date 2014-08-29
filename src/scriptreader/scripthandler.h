#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <QObject>


class QXmlStreamReader;


class ScriptHandler : public QObject
{
    Q_OBJECT
public:
    explicit ScriptHandler(QObject *parent = 0);

    virtual void invalid(/*const*/ QXmlStreamReader& xml);
    virtual void startDocument(const QXmlStreamReader& xml);
    virtual void endDocument(const QXmlStreamReader& xml);
    virtual void startElement(/*const*/ QXmlStreamReader& xml);
    virtual void endElement(const QXmlStreamReader& xml);
    virtual void characters(const QXmlStreamReader& xml);
    virtual void comment(const QXmlStreamReader& xml);
    virtual void dtd(const QXmlStreamReader& xml);
    virtual void entityReference(const QXmlStreamReader& xml);
    virtual void processingInstruction(const QXmlStreamReader& xml);

protected:
    QString tokenString(const QXmlStreamReader &xml) const;


signals:

public slots:

};


class ElementHandler : public QObject
{
    Q_OBJECT
public:
    explicit ElementHandler(QObject *parent = 0);


};

class ExperimentHandler : public ScriptHandler
{
    Q_OBJECT
public:
    explicit ExperimentHandler(QObject *parent = 0) : ScriptHandler(parent) {}

    virtual void startElement(/*const*/ QXmlStreamReader& xml);
    virtual void endElement(const QXmlStreamReader& xml);


};

#endif // SCRIPTHANDLER_H
