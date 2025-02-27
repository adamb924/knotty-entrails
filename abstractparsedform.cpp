#include "abstractparsedform.h"

#include "morphology.h"

#include <QXmlStreamWriter>
#include <QDomDocument>

using namespace KE;

AbstractParsedForm::AbstractParsedForm()
{

}

AbstractParsedForm::~AbstractParsedForm()
{

}

void AbstractParsedForm::setForm(const ME::Form &form, const ME::Morphology *morphology)
{
    Q_ASSERT(morphology != nullptr);

    setForm(form);

    const QList<ME::Parsing> ps = morphology->possibleParsings( form );
    setWellformedness( ps.count() );
    if( ps.count() > 0 )
    {
        setParsing(ps.first());
    }
}

void AbstractParsedForm::setParsing(const ME::Morphology *morphology)
{
    const QList<ME::Parsing> ps = morphology->possibleParsings( form() );
    setWellformedness(ps.count());
    if( ! ps.isEmpty() )
    {
        setParsing( ps.first() );
    }
}

QString AbstractParsedForm::summary()
{
    QString dbgString;
    QTextStream dbg(&dbgString);

    dbg << "AbstractParsedForm(";
    dbg << "Form: " << form().summary();
    dbg << ", Wellformedness: " << AbstractTextItem::wellformednessToString( wellformedness() );
    if( ! parsing().isNull() )
    {
        dbg << ", Parsing: " << parsing().summary();
    }
    else
    {
        dbg << ", No Parsings";
    }
    dbg << ")";

    return dbgString;
}

void AbstractParsedForm::setWellformednessFromMorphology(const ME::Morphology *morphology)
{
    int numberOfParsings = morphology->possibleParsings( form() ).count();
    setWellformedness(numberOfParsings);
}

void AbstractParsedForm::setWellformedness(int numberOfParsings)
{
    setWellformedness( AbstractTextItem::wellformednessStatusFromNumberOfParsings(numberOfParsings) );
}

bool AbstractParsedForm::isWellformed() const
{
    return AbstractTextItem::isWellformed( wellformedness() );
}

void AbstractParsedForm::serialize(const QString &elementName, QXmlStreamWriter &out)
{
    out.writeStartElement(elementName);
    out.writeAttribute( "wellformed", AbstractTextItem::wellformednessToString( wellformedness() ) );
    out.writeAttribute( "source", source() );
    if( !glossaryKey().isEmpty() )
        out.writeAttribute("glossary", glossaryKey());

    form().serialize(out);

    if( !parsing().isNull() )
        parsing().serialize(out, true);

    out.writeEndElement(); /// elementName
}

QDomElement AbstractParsedForm::toElement(const QString &elementName, QDomDocument *document)
{
    QString serialized;
    QXmlStreamWriter stream(&serialized);
    serialize(elementName, stream);
    QDomDocument xmlDoc;
    xmlDoc.setContent(serialized);
    return document->importNode( xmlDoc.firstChild().toElement(), true ).toElement();
}
