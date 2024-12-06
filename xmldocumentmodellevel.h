#ifndef XMLDOCUMENTMODELLEVEL_H
#define XMLDOCUMENTMODELLEVEL_H

#include "knotty-entrails_global.h"

#include <QStringList>
#include <QXmlStreamReader>
#include <QDomNode>

#include "xmldocumentposition.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT XmlDocumentModelLevel
{
public:
    enum Type { None, Root, Major, Minor };

    XmlDocumentModelLevel();

    QStringList elementNames() const;
    void setElementNames(const QStringList &elementNames);

    Type type() const;
    void setType(const Type &type);
    void setType(const QString &type);

    bool containsText() const;
    void setContainsText(bool containsText);

    void addChild(XmlDocumentModelLevel child);

    const XmlDocumentModelLevel *matchingChildElement(QXmlStreamReader & in) const;

    QString summary() const;

    QString label(QDomElement node) const;

    bool matchesElementName(const QString & elementName) const;
    bool matchesElementName(QDomNode node) const;

    static XmlDocumentModelLevel readFromXml(QXmlStreamReader & in);

    QList<XmlDocumentPosition> matchingChildren(QDomElement parent) const;

    static QString XML_DOCUMENT_MODEL;
    static QString XML_DOCUMENT_LEVEL;
    static QString XML_DOCUMENT_TYPE;
    static QString XML_DOCUMENT_LABEL;
    static QString XML_DOCUMENT_HAS_TEXT;
    static QString XML_DOCUMENT_LABEL_FROM;
    static QString XML_DOCUMENT_ELEMENTS;

    static Type typeFromString(const QString & str);
    static QString typeToString(Type t);

    void setLabelFrom(const QString &newLabelFrom);

    QList<XmlDocumentPosition> elementsAtLevel(QDomElement parent, Type type) const;

private:
    QStringList mElementNames;
    Type mType;
    bool mContainsText;
    QList<XmlDocumentModelLevel> mModelChildren;
    QString mLabelFrom;
};

} // namespace KE

#endif // XMLDOCUMENTMODELLEVEL_H
