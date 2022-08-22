#ifndef XMLDOCUMENTMODEL_H
#define XMLDOCUMENTMODEL_H

#include "knotty-entrails_global.h"

#include "xmldocumentmodellevel.h"
#include "xmldocumentposition.h"

#include <QStringList>
#include <QXmlStreamReader>

class KNOTTYENTRAILS_EXPORT XmlDocumentModel : public XmlDocumentModelLevel
{
public:
    XmlDocumentModel();

    QString label() const;
    void setLabel(const QString &label);

    static XmlDocumentModel readFromXml(QXmlStreamReader & in);
    static XmlDocumentModel readFromXml(const QString & path);

    QString summary() const;

    const XmlDocumentModelLevel &root() const;

    XmlDocumentPosition getRootPosition(QDomDocument document) const;

    QList<XmlDocumentPosition> getMajorDivisions(QDomDocument document) const;
    QList<XmlDocumentPosition> getMajorDivisions(XmlDocumentPosition root) const;

private:
    QString mLabel;
    XmlDocumentModelLevel mRoot;
};

#endif // XMLDOCUMENTMODEL_H
