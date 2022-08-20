#ifndef XMLDOCUMENTMODEL_H
#define XMLDOCUMENTMODEL_H

#include "knotty-entrails_global.h"

#include "xmldocumentmodellevel.h"

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

    QList<QDomNode> getRootDivisions(QDomDocument document);
    QList<QDomNode> getMajorDivisions(QDomDocument document);

private:
    QString mLabel;
    XmlDocumentModelLevel mRoot;
};

#endif // XMLDOCUMENTMODEL_H
