#include "elementreader.h"

#include <QDebug>
#include <QXmlStreamReader>


XmlElementReader::XmlElementReader(QXmlStreamReader *stream)
        : stream_(stream)
{}


GlobalElementReader::GlobalElementReader(QXmlStreamReader *stream)
        : XmlElementReader(stream)
{
    readGlobal();
}

void GlobalElementReader::readGlobal() {
    Q_ASSERT(stream_->isStartElement() && stream_->name() == "global");

    while (stream_->readNextStartElement()) {
        if (stream_->name() == "variable") {
            qDebug()
                    << stream_->name()
                    << " [" << stream_->attributes().value("atc:name")
                    << ", " << stream_->attributes().value("atc:type")
                    << " = " << stream_->attributes().value("atc:int")
                    << "]";
            stream_->skipCurrentElement();
        }
        else
                stream_->raiseError(QObject::tr("Unrecognised tag <%1>!")
                        .arg(stream_->name().toString())
                    );
    }


}
