#ifndef XMLELEMENTREADER_H
#define XMLELEMENTREADER_H


class QXmlStreamReader;


class XmlElementReader
{
public:
    XmlElementReader(QXmlStreamReader *stream);


protected:
    QXmlStreamReader *stream_;

};


class GlobalElementReader : public XmlElementReader
{
public:
    GlobalElementReader(QXmlStreamReader *stream);

private:
    void readGlobal();

};

#endif // XMLELEMENTREADER_H
