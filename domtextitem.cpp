#include "domtextitem.h"

#include <QXmlStreamWriter>

#include "morphology.h"

using namespace KE;

QString DomTextItem::XML_TYPE = "type";
QString DomTextItem::XML_INPUT = "input";
QString DomTextItem::XML_OUTPUT = "output";
QString DomTextItem::XML_MODIFIABLE = "modifiable";
QString DomTextItem::XML_TRUE = "true";
QString DomTextItem::XML_FALSE = "false";

DomTextItem::DomTextItem(const QDomElement & textItem, const ME::Morphology *morphology)
    : mTextItemElement(textItem)
{
    QDomElement inputElement, outputElement;
    QDomNodeList outputList = textItem.elementsByTagName(XML_OUTPUT);
    if( outputList.count() > 0 )
    {
        outputElement = outputList.at(0).toElement();
    }

    QDomNodeList inputList = textItem.elementsByTagName(XML_INPUT);
    if( inputList.count() > 0 )
    {
        inputElement = inputList.at(0).toElement();
    }

    ensureElementExists(inputElement, XML_INPUT);
    ensureElementExists(outputElement, XML_OUTPUT);

    mInput = new DomParsedForm( inputElement, morphology );
    mOutput = new DomParsedForm( outputElement, morphology );
}

DomTextItem::~DomTextItem()
{
    delete mInput;
    delete mOutput;
}

AbstractTextItem::Type DomTextItem::type() const
{
    return AbstractTextItem::typeFromString( mTextItemElement.attribute(XML_TYPE) );
}

bool DomTextItem::modifiable() const
{
    return mTextItemElement.attribute(XML_MODIFIABLE) == XML_TRUE;
}

void DomTextItem::setModifiable(bool modifiable)
{
    mTextItemElement.setAttribute(XML_MODIFIABLE, modifiable ? XML_TRUE : XML_FALSE );
}

AbstractParsedForm &DomTextItem::input()
{
    return *mInput;
}

AbstractParsedForm &DomTextItem::output()
{
    return *mOutput;
}

const AbstractParsedForm &DomTextItem::input() const
{
    return *mInput;
}

const AbstractParsedForm &DomTextItem::output() const
{
    return *mOutput;
}

QDomElement DomTextItem::element() const
{
    return mTextItemElement;
}

void DomTextItem::ensureElementExists(QDomElement &element, const QString &elementName)
{
    Q_ASSERT( !mTextItemElement.isNull() );
    if( element.isNull() )
    {
        element = mTextItemElement.ownerDocument().createElement(elementName);
        mTextItemElement.appendChild(element);
    }
}
