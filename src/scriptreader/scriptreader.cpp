#include "scriptreader.h"

#include <QDebug>
#include <QIODevice>

#include <stdexcept>

#include "scripthandler.h"
#include "elementreader.h"


ScriptReader::ScriptReader(QObject *parent)
        : QObject(parent)
        , xml_()
        , hdlrs_()
{
   hdlrs_.push(new ScriptHandler(this));
}


bool ScriptReader::read(QIODevice *device) {
    xml_.setDevice(device);

    while (auto tokentype = xml_.readNext()) {
        switch (tokentype) {

        //
        case QXmlStreamReader::StartElement: startElement(); break;

        //
        case QXmlStreamReader::Invalid: hdlrs_.top()->invalid(xml_); goto Exit;
        case QXmlStreamReader::StartDocument: hdlrs_.top()->startDocument(xml_); break;
        case QXmlStreamReader::EndDocument: hdlrs_.top()->endDocument(xml_); goto Exit;
        case QXmlStreamReader::EndElement: hdlrs_.top()->endElement(xml_); break;
        case QXmlStreamReader::Characters: hdlrs_.top()->characters(xml_); break;
        case QXmlStreamReader::Comment: hdlrs_.top()->comment(xml_); break;
        case QXmlStreamReader::DTD: hdlrs_.top()->dtd(xml_); break;
        case QXmlStreamReader::EntityReference: hdlrs_.top()->entityReference(xml_); break;
        case QXmlStreamReader::ProcessingInstruction: hdlrs_.top()->processingInstruction(xml_); break;

        // Catch-all, should never execute!
        default:
            xml_.raiseError(QObject::tr("Unrecognised Token Type <%1>!").arg(tokentype));
            //throw std::logic_error("Illegal QXmlStreamReader::TokenType!");
        }
    }

Exit:
    return !xml_.error();
}

QString ScriptReader::errorString() const {
    return xml_.errorString();
}

//
//
//

void ScriptReader::startElement() {
    setHandler(xml_.name());
    hdlrs_.top()->startElement(xml_);
}

void ScriptReader::setHandler(const QStringRef identifier) {
    hdlrs_.push(new ExperimentHandler(this));
}


////
////
////

//void ScriptReader::readExperiment() {
//    Q_ASSERT(xml_.isStartElement() && xml_.name() == "experiment");
//    qDebug() << xml_.name() << " [" << xml_.attributes().value("atc:idx") << "]";

//    while (xml_.readNextStartElement()) {
//        if ("global" == xml_.name()) {
//                //readGlobal();
//                GlobalElementReader ger(&xml_);
//        }
//        else if ("config" == xml_.name()) readConfig();
//        else if ("data" == xml_.name()) readData();
//        else if ("presentation" == xml_.name()) readPresentation();
//        else
//            xml_.raiseError(QObject::tr("Unrecognised tag <%1>!")
//                    .arg(xml_.name().toString())
//                );
//    }
//}

//void ScriptReader::readGlobal() {
//    qDebug() << xml_.name();
//    while (xml_.readNextStartElement()) {
//        if (xml_.name() == "variable") {
//            qDebug()
//                    << xml_.name() << " [" << xml_.attributes().value("atc:name")
//                    << ", " << xml_.attributes().value("atc:type") << " = "
//                    << xml_.attributes().value("atc:init") << "]";
//            xml_.skipCurrentElement();
//        }
//        else
//                xml_.raiseError(QObject::tr("Unrecognised tag <%1>!")
//                        .arg(xml_.name().toString())
//                    );
//    }

//}
//void ScriptReader::readConfig() {
//    qDebug() << xml_.name();
//    xml_.skipCurrentElement();
//}
//void ScriptReader::readData() {
//    qDebug() << xml_.name();
//    xml_.skipCurrentElement();
//}
//void ScriptReader::readPresentation() {
//    qDebug() << xml_.name();
//    xml_.skipCurrentElement();
//}
