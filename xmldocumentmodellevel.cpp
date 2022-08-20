#include "xmldocumentmodellevel.h"

#include <QtDebug>

QString XmlDocumentModelLevel::XML_DOCUMENT_MODEL = "document-model";
QString XmlDocumentModelLevel::XML_DOCUMENT_LEVEL = "level";

QString XmlDocumentModelLevel::XML_DOCUMENT_TYPE = "type";
QString XmlDocumentModelLevel::XML_DOCUMENT_LABEL = "label";
QString XmlDocumentModelLevel::XML_DOCUMENT_LABEL_FROM = "label-from";
QString XmlDocumentModelLevel::XML_DOCUMENT_HAS_TEXT = "contains-text";
QString XmlDocumentModelLevel::XML_DOCUMENT_ELEMENTS = "elements";

XmlDocumentModelLevel::XmlDocumentModelLevel() : mType(None), mContainsText(false)
{

}

QStringList XmlDocumentModelLevel::elementNames() const
{
    return mElementNames;
}

void XmlDocumentModelLevel::setElementNames(const QStringList &elementNames)
{
    mElementNames = elementNames;
}

XmlDocumentModelLevel::Type XmlDocumentModelLevel::type() const
{
    return mType;
}

void XmlDocumentModelLevel::setType(const Type &type)
{
    mType = type;
}

void XmlDocumentModelLevel::setType(const QString &type)
{
    mType = typeFromString(type);
}

bool XmlDocumentModelLevel::containsText() const
{
    return mContainsText;
}

void XmlDocumentModelLevel::setContainsText(bool containsText)
{
    mContainsText = containsText;
}

void XmlDocumentModelLevel::addChild(XmlDocumentModelLevel child)
{
    mChildren << child;
}

const XmlDocumentModelLevel *XmlDocumentModelLevel::matchingChildElement(QXmlStreamReader &in) const
{
    for(int i=0; i<mChildren.count(); i++)
    {
        if( mChildren.at(i).elementNames().contains( in.name() ) )
            return &mChildren.at(i);
    }
    return nullptr;
}

QString XmlDocumentModelLevel::summary() const
{
    QString str = "Level(" + mElementNames.join(", ") + "; " + typeToString(mType);
    if( !mLabelFrom.isEmpty() )
        str += "; " + mLabelFrom;
    if( mContainsText )
        str += "; contains text";
    str += ")";
    if( mChildren.count() > 0 )
    {
        str += " { ";
        for(int i=0; i<mChildren.count(); i++)
        {
            str += mChildren.at(i).summary();
        }
        str += " }";
    }
    return str;
}

XmlDocumentModelLevel XmlDocumentModelLevel::readFromXml(QXmlStreamReader &in)
{
    XmlDocumentModelLevel model;

    Q_ASSERT( in.name().toString() == XML_DOCUMENT_LEVEL );

    model.setType( in.attributes().value( XML_DOCUMENT_TYPE ).toString() );
    model.setContainsText( in.attributes().value( XML_DOCUMENT_HAS_TEXT ).toString() == "true" );
    model.setLabelFrom( in.attributes().value( XML_DOCUMENT_LABEL_FROM ).toString() );
    model.setElementNames( in.attributes().value( XML_DOCUMENT_ELEMENTS ).toString().split(" ") );

    while( !in.atEnd() && !in.isEndElement() )
    {
        /// TODO this logic isn't quite correct; won't handle more deeply nested structures
        in.readNext();
        if( in.isStartElement() && in.name() == XML_DOCUMENT_LEVEL )
        {
            model.addChild( readFromXml(in) );
        }
    }

    return model;
}

QList<QDomNode> XmlDocumentModelLevel::matchingChildren(QDomNode parent) const
{
    QList<QDomNode> list;

    QDomNodeList allChildren = parent.childNodes();
    for(int i=0; i<allChildren.count(); i++)
    {
        if( allChildren.at(i).isElement() && mElementNames.contains( allChildren.at(i).nodeName() ) )
            list << allChildren.at(i);
    }

    return list;
}

XmlDocumentModelLevel::Type XmlDocumentModelLevel::typeFromString(const QString &str)
{
    if( str == "root" )
    {
        return XmlDocumentModelLevel::Root;
    }
    else if ( str == "major" )
    {
        return XmlDocumentModelLevel::Major;
    }
    else if ( str == "minor" )
    {
        return XmlDocumentModelLevel::Minor;
    }
    return XmlDocumentModelLevel::Minor;
}

QString XmlDocumentModelLevel::typeToString(Type t)
{
    switch(t)
    {
    case XmlDocumentModelLevel::None:
        return "none";
    case XmlDocumentModelLevel::Root:
        return "root";
    case XmlDocumentModelLevel::Major:
        return "major";
    case XmlDocumentModelLevel::Minor:
        return "minor";
    }
    return "";
}

const QString &XmlDocumentModelLevel::labelFrom() const
{
    return mLabelFrom;
}

void XmlDocumentModelLevel::setLabelFrom(const QString &newLabelFrom)
{
    mLabelFrom = newLabelFrom;
}

const QList<XmlDocumentModelLevel> &XmlDocumentModelLevel::children() const
{
    return mChildren;
}
