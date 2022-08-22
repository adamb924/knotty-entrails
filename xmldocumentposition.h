#ifndef XMLDOCUMENTPOSITION_H
#define XMLDOCUMENTPOSITION_H

#include "knotty-entrails_global.h"

#include <QDomElement>

class XmlDocumentModelLevel;

class KNOTTYENTRAILS_EXPORT XmlDocumentPosition
{
public:
    XmlDocumentPosition(const XmlDocumentModelLevel * level, QDomElement node);
    XmlDocumentPosition(const XmlDocumentPosition & other);
    XmlDocumentPosition &operator=(const XmlDocumentPosition & other);

    const XmlDocumentModelLevel *level() const;

    const QDomElement &node() const;

    const QString label() const;

private:
    const XmlDocumentModelLevel * mLevel;
    QDomElement mNode;
};

#endif // XMLDOCUMENTPOSITION_H
