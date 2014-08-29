#include "scripthandler.h"

#include <QDebug>
#include <QXmlStreamReader>


ScriptHandler::ScriptHandler(QObject *parent) :
    QObject(parent)
{}

void ScriptHandler::invalid(/*const*/ QXmlStreamReader &xml) {
    xml.raiseError(
            QObject::tr("This is not a valid ATClab file.\nat line %1, column %2\nCause:\n\t(%3) %4")
            .arg(xml.lineNumber())
            .arg(xml.columnNumber())
            .arg(xml.error())
            .arg(xml.errorString())
        );
    qDebug() << xml.errorString();
}

void ScriptHandler::startDocument(const QXmlStreamReader &xml) {
/*
    xml.documentVersion();
    xml.documentEncoding();
    xml.isStandaloneDocument();
*/
    ;
//    handler_ = new ScriptHandler(this);
}

void ScriptHandler::endDocument(const QXmlStreamReader &xml) {
    ;
}

void ScriptHandler::startElement(/*const*/ QXmlStreamReader &xml) {
    qDebug()
            << "[4] START_ELEMENT : "
            << xml.namespaceUri() << "/"
            << xml.name() << " ["
            << xml.attributes().size() << ", "
            << xml.namespaceDeclarations().size() << "]";
}

void ScriptHandler::endElement(const QXmlStreamReader &xml) {
    qDebug()
            << "[5] END_ELEMENT : "
            << xml.namespaceUri() << "/"
            << xml.name();

}

void ScriptHandler::characters(const QXmlStreamReader &xml) {
    if (xml.isWhitespace())
            qDebug()
                    << tokenString(xml) << "(WHITE_SPACE_ONLY)";
     else
            qDebug()
                    << "[6] ("
                    << xml.isCDATA() << ") "
                    << xml.text();
}

void ScriptHandler::comment(const QXmlStreamReader &xml) {
    qDebug()
            << "[7] COMMENT :"
            << xml.text();
}

void ScriptHandler::dtd(const QXmlStreamReader &xml) {
    qDebug()
            << "[8] DTD : ("
            << xml.notationDeclarations().size() << ", "
            << xml.entityDeclarations().size() << ") ["
            << xml.dtdName() << ", "
            << xml.dtdPublicId() << ", "
            << xml.dtdSystemId() << "] "
            << xml.text();
}

void ScriptHandler::entityReference(const QXmlStreamReader &xml) {
    qDebug()
            << "[9] ENTITY_REFERENCE : "
            << xml.name() << ", "
            << xml.text();
}

void ScriptHandler::processingInstruction(const QXmlStreamReader &xml) {
    qDebug()
            << "[10] PROCESSING_INSTRUCTION : "
            << xml.processingInstructionTarget() << "->"
            << xml.processingInstructionData();
}

QString ScriptHandler::tokenString(const QXmlStreamReader &xml) const {
    return QObject::tr("[%1] %2:").arg(xml.tokenType()).arg(xml.tokenString());
}

//------------------------------------------------------------------------------------
//
//


void ExperimentHandler::startElement(/*const*/ QXmlStreamReader &xml) {
    Q_ASSERT(xml.isStartElement() && xml.name() == "experiment");
    qDebug() << xml.name() << " [" << xml.attributes().value("atc:idx") << "]";

    /*
     * experiment handler already loaded!
     *
     * possible next elements:
     *
     *          global
     *          config
     *          data
     *          presentation
     */

}

void ExperimentHandler::endElement(const QXmlStreamReader &xml) {
    Q_ASSERT(xml.isEndElement() && xml.name() == "experiment");
    qDebug() << xml.name() << " [" << xml.attributes().value("atc:idx") << "]";
}
