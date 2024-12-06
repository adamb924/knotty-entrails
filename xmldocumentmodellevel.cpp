#include "xmldocumentmodellevel.h"

#include <QtDebug>

#include "xmldocumentposition.h"

using namespace KE;

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
    mModelChildren << child;
}

const XmlDocumentModelLevel *XmlDocumentModelLevel::matchingChildElement(QXmlStreamReader &in) const
{
    for(int i=0; i<mModelChildren.count(); i++)
    {
        if( mModelChildren.at(i).elementNames().contains( in.name() ) )
            return &mModelChildren.at(i);
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
    if( mModelChildren.count() > 0 )
    {
        str += " { ";
        for(int i=0; i<mModelChildren.count(); i++)
        {
            str += mModelChildren.at(i).summary();
        }
        str += " }";
    }
    return str;
}

QString XmlDocumentModelLevel::label(QDomElement node) const
{
    return node.attribute( mLabelFrom );
}

bool XmlDocumentModelLevel::matchesElementName(const QString &elementName) const
{
    return mElementNames.contains( elementName );
}

bool XmlDocumentModelLevel::matchesElementName(QDomNode node) const
{
    return mElementNames.contains( node.localName() );
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

QList<XmlDocumentPosition> XmlDocumentModelLevel::matchingChildren(QDomElement parent) const
{
    QList<XmlDocumentPosition> list;

    QDomNodeList children = parent.childNodes();

    for(int i=0; i<children.count(); i++)
    {
        if( children.at(i).isElement() )
        {
            for(int j=0; j<mModelChildren.count(); j++)
            {
                if( mModelChildren.at(j).matchesElementName( children.at(i) ) )
                {
                    list << XmlDocumentPosition( &mModelChildren[j], children.at(i).toElement() );
                }
            }
        }
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

void XmlDocumentModelLevel::setLabelFrom(const QString &newLabelFrom)
{
    mLabelFrom = newLabelFrom;
}

QList<XmlDocumentPosition> XmlDocumentModelLevel::elementsAtLevel(QDomElement parent, Type type) const
{
    QList<XmlDocumentPosition> returnList;

    QList<XmlDocumentPosition> children = matchingChildren(parent);
    if( children.isEmpty() ) return returnList;
    for(int i=0; i<children.count(); i++)
    {
        if( children.at(i).level()->type() == type )
        {
            returnList << children.at(i);
        }
    }
    if( ! returnList.isEmpty() )
    {
        return returnList;
    }
    else
    {
        for(int i=0; i<children.count(); i++)
        {
            returnList << children.at(i).level()->elementsAtLevel( children.at(i).node(), type );
        }
    }
    return returnList;
}
