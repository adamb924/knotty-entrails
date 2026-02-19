#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <QStringList>
#include "knotty-entrails_global.h"

class QXmlStreamReader;

namespace KE {

class KNOTTYENTRAILS_EXPORT DocumentModel
{
public:
    DocumentModel();

    bool isInclude(QXmlStreamReader &in);
    bool isExclude(QXmlStreamReader &in);

    static DocumentModel readXml(QXmlStreamReader &in);

    static QString XML_DOCUMENT_MODEL;

    QString summary() const;

    QStringList pageElements() const;

    QStringList paragraphElements() const;

private:
    static DocumentModel readXml(const QString &path);

    static QString XML_INCLUDE;
    static QString XML_EXCLUDE;
    static QString XML_SRC;
    static QString XML_PAGE;
    static QString XML_PARAGRAPH;

    QStringList mInclude;
    QStringList mExclude;
    QStringList mPageElements;
    QStringList mParagraphElements;
};

} // namespace KE

#endif // DOCUMENTMODEL_H
