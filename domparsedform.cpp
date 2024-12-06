#include "domparsedform.h"

#include "morphology.h"

using namespace KE;

QString DomParsedForm::XML_ID = "id";
QString DomParsedForm::XML_LANG = "lang";
QString DomParsedForm::XML_FORM = "form";
QString DomParsedForm::XML_WELLFORMED = "wellformed";
QString DomParsedForm::XML_PARSING = "parsing";
QString DomParsedForm::XML_PARSING_SUMMARY = "parsing-summary";
QString DomParsedForm::XML_PARSING_IDENTIFIER = "parsing-identifier";
QString DomParsedForm::XML_SOURCE = "source";
QString DomParsedForm::XML_GLOSSARY = "glossary";

DomParsedForm::DomParsedForm(const QDomElement &textItem, const ME::Morphology *morphology) : mParsedFormElement(textItem), mMorphology(morphology)
{
    QDomNodeList outputList = textItem.elementsByTagName(XML_FORM);
    if( outputList.count() > 0 )
    {
        mFormElement = outputList.at(0).toElement();
    }

    ensureElementExists( mFormElement, XML_FORM );
}

DomParsedForm::~DomParsedForm()
{

}

ME::Form DomParsedForm::form() const
{
    bool ok;
    qlonglong id = mFormElement.attribute(XML_ID).toLongLong(&ok);
    if( !ok )
        id = -1; /// this is the default null value

    ME::WritingSystem ws = mMorphology->writingSystem( mFormElement.attribute(XML_LANG) );

    return ME::Form( ws, mFormElement.text(), id );
}

void DomParsedForm::setForm(const ME::Form &form)
{
    ensureElementExists( mFormElement, XML_FORM );
    Q_ASSERT( !mFormElement.isNull() );

    mFormElement.setAttribute(XML_LANG, form.writingSystem().abbreviation() );
    QDomText newNode = mFormElement.ownerDocument().createTextNode( form.text() );

    if( mFormElement.firstChild().isNull() )
    {
        mFormElement.appendChild( newNode );
    }
    else
    {
        mFormElement.replaceChild( newNode, mFormElement.firstChild() );
    }
}

AbstractTextItem::WellformednessStatus DomParsedForm::wellformedness() const
{
    return AbstractTextItem::wellformednessFromString( mParsedFormElement.attribute(XML_WELLFORMED) );
}

void DomParsedForm::setWellformedness(AbstractTextItem::WellformednessStatus wellformedness)
{
    mParsedFormElement.setAttribute(XML_WELLFORMED, AbstractTextItem::wellformednessToString(wellformedness) );
}

QString DomParsedForm::glossaryKey() const
{
    return mParsedFormElement.attribute(XML_GLOSSARY);

}

void DomParsedForm::setGlossaryKey(const QString &glossaryKey)
{
    mParsedFormElement.setAttribute(XML_GLOSSARY, glossaryKey);

}

QString DomParsedForm::source() const
{
    return mParsedFormElement.attribute(XML_SOURCE);
}

void DomParsedForm::setSource(const QString &source)
{
    mParsedFormElement.setAttribute(XML_SOURCE, source );
}

ME::Parsing DomParsedForm::parsing()
{
    Q_ASSERT(mMorphology != nullptr);

    if( mCachedParsing.isNull() )
    {
        QDomNodeList parseList = mParsedFormElement.elementsByTagName(XML_PARSING);
        if( parseList.count() > 0 )
        {
            const ME::Parsing p = ME::Parsing::readFromXml( parseList.at(0).toElement(), mMorphology);
            if( p.isNull() )
            {
                mParsedFormElement.removeChild( parseList.at(0) );
            }
            return p;
        }
        else
        {
            return ME::Parsing();
        }
    }
    else
    {
        return mCachedParsing;
    }
}

void DomParsedForm::setParsing(const ME::Parsing &p)
{
    mCachedParsing = p;

    QDomNodeList parseList = mParsedFormElement.elementsByTagName(XML_PARSING);
    for(int i=0; i<parseList.count(); i++)
    {
        mParsedFormElement.removeChild( parseList.at(i) );
    }

    QDomElement parsingEl = mParsedFormElement.ownerDocument().createElement(XML_PARSING);
    p.serialize(parsingEl, true);
    Q_ASSERT( !mParsedFormElement.isNull() );
    mParsedFormElement.appendChild(parsingEl);

    setWellformedness( AbstractTextItem::WellformedUnknown );
    /// set the parsing identifier
    setParsingIdentifier( p.labelSummary() );
}

QString DomParsedForm::parsingIdentifier() const
{
    return mParsedFormElement.attribute(XML_PARSING_IDENTIFIER);
}

void DomParsedForm::setParsingIdentifier(const QString &identifier)
{
    mParsedFormElement.setAttribute(XML_PARSING_IDENTIFIER, identifier);
}

void DomParsedForm::ensureElementExists(QDomElement &element, const QString &elementName)
{
    Q_ASSERT( !mParsedFormElement.isNull() );
    if( element.isNull() )
    {
        element = mParsedFormElement.ownerDocument().createElement(elementName);
        mParsedFormElement.appendChild(element);
    }
}
