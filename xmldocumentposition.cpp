#include "xmldocumentposition.h"

#include "xmldocumentmodellevel.h"

XmlDocumentPosition::XmlDocumentPosition(const XmlDocumentModelLevel * level, QDomElement node)
    : mLevel(level),mNode(node)
{

}

XmlDocumentPosition::XmlDocumentPosition(const XmlDocumentPosition &other) : mLevel(other.mLevel), mNode(other.mNode)
{
}

XmlDocumentPosition &XmlDocumentPosition::operator =(const XmlDocumentPosition &other)
{
    mLevel = other.mLevel;
    mNode = other.mNode;
    return *this;
}

const XmlDocumentModelLevel *XmlDocumentPosition::level() const
{
    return mLevel;
}

const QDomElement &XmlDocumentPosition::node() const
{
    return mNode;
}

const QString XmlDocumentPosition::label() const
{
    return mLevel->label( mNode );
}
