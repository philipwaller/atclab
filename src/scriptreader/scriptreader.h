#ifndef SCRIPTREADER_H
#define SCRIPTREADER_H

#include "scriptreader_global.h"

#include <QObject>
#include <QStack>
#include <QXmlStreamReader>


class ScriptHandler;
class QIODevice;


class SCRIPTREADERSHARED_EXPORT ScriptReader : public QObject
{
    Q_OBJECT
public:
    explicit ScriptReader(QObject *parent = 0);
    ~ScriptReader() {}

    bool read(QIODevice *device);
    QString errorString() const;

    //void registerElementReader(const QString name, XmlElementReader *reader);


private:
    void startElement();

    void setHandler(const QStringRef identifier);

//    void readExperiment();
//    void readGlobal();
//    void readConfig();
//    void readData();
//    void readPresentation();


private:
    QXmlStreamReader xml_;
    QStack<ScriptHandler*> hdlrs_;
};

#endif // SCRIPTREADER_H
