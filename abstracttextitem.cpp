#include "abstracttextitem.h"

#include <QXmlStreamWriter>

#include <QDomDocument>
#include <QDomElement>

#include "abstractparsedform.h"

using namespace KE;

AbstractTextItem::AbstractTextItem()
{
}

AbstractTextItem::~AbstractTextItem()
{

}

QString AbstractTextItem::summary()
{
    QString dbgString;
    QTextStream dbg(&dbgString);

    dbg << "AbstractTextItem(";
    dbg << "Type: " << typeString();
    dbg << ", Input: " << input().summary();
    dbg << ", Output: " << output().summary();
    dbg << ")";

    return dbgString;
}

void AbstractTextItem::serialize(QXmlStreamWriter &out)
{
    out.writeStartElement("text-item");
    out.writeAttribute( "type", AbstractTextItem::typeToString( type() ) );
    out.writeAttribute( "modifiable", modifiable() ? "true" : "false" );
    output().serialize("output", out);
    if (type() == AbstractTextItem::Translated)
        input().serialize("input", out);
    out.writeEndElement(); /// text-item
}

QDomElement AbstractTextItem::toElement(QDomDocument document)
{
    QString serialized;
    QXmlStreamWriter stream(&serialized);
    serialize(stream);
    QDomDocument xmlDoc;
    xmlDoc.setContent(serialized);
    return document.importNode(xmlDoc.firstChild().toElement(), true).toElement();
}

QString AbstractTextItem::typeToString(AbstractTextItem::Type type)
{
    switch( type )
    {
    case AbstractTextItem::Simple:
        return "simple";
    case AbstractTextItem::Translated:
        return "translated";
    case AbstractTextItem::Null:
        return "null";
    }
    return "";
}

AbstractTextItem::Type AbstractTextItem::typeFromString(const QString &type)
{
    if( type == "simple" )
        return AbstractTextItem::Simple;
    else if ( type == "translated" )
        return AbstractTextItem::Translated;
    else
        return AbstractTextItem::Null;
}

QString AbstractTextItem::wellformednessToString(AbstractTextItem::WellformednessStatus wf)
{
    switch( wf )
    {
    case AbstractTextItem::Untested:
        return "untested";
    case AbstractTextItem::WellformedSingle:
        return "wellformed-single";
    case AbstractTextItem::WellformedMultiple:
        return "wellformed-multiple";
    case AbstractTextItem::WellformedUnknown:
        return "wellformed-unknown";
    case AbstractTextItem::NotWellformed:
        return "notwellformed";
    case AbstractTextItem::Ignored:
        return "ignored";
    }
    return "";
}

AbstractTextItem::WellformednessStatus AbstractTextItem::wellformednessFromString(const QString &type)
{
    if( type == "wellformed-single" )
        return AbstractTextItem::WellformedSingle;
    else if( type == "wellformed-multiple" )
        return AbstractTextItem::WellformedMultiple;
    else if( type == "wellformed-unknown" )
        return AbstractTextItem::WellformedUnknown;
    else if ( type == "notwellformed" )
        return AbstractTextItem::NotWellformed;
    else if ( type == "ignored" )
        return AbstractTextItem::Ignored;
    else
        return AbstractTextItem::Untested;
}

AbstractTextItem::WellformednessStatus AbstractTextItem::wellformednessStatusFromNumberOfParsings(int numberOfParsings)
{
    Q_ASSERT(numberOfParsings >= 0);
    if( numberOfParsings == 0 )
        return AbstractTextItem::NotWellformed;
    else if( numberOfParsings == 1 )
        return AbstractTextItem::WellformedSingle;
    else
        return AbstractTextItem::WellformedMultiple;
}

bool AbstractTextItem::isWellformed(AbstractTextItem::WellformednessStatus status)
{
    return status == AbstractTextItem::WellformedMultiple
            || status == AbstractTextItem::WellformedSingle
            || status == AbstractTextItem::WellformedUnknown;
}

QString AbstractTextItem::typeString() const
{
    return AbstractTextItem::typeToString( type() );
}
