#include "documentmodel.h"

#include <QFile>
#include <QXmlStreamReader>

using namespace KE;

QString DocumentModel::XML_DOCUMENT_MODEL = "document-model";
QString DocumentModel::XML_INCLUDE = "include";
QString DocumentModel::XML_EXCLUDE = "exclude";
QString DocumentModel::XML_SRC = "src";
QString DocumentModel::XML_PAGE = "page";
QString DocumentModel::XML_PARAGRAPH = "paragraph";

DocumentModel::DocumentModel() {}

bool DocumentModel::isInclude(QXmlStreamReader &in)
{
    return mInclude.contains(in.name());
}

bool DocumentModel::isExclude(QXmlStreamReader &in)
{
    return mExclude.contains(in.name());
}

DocumentModel DocumentModel::readXml(QXmlStreamReader &in)
{
    Q_ASSERT(in.isStartElement() && in.name() == KE::DocumentModel::XML_DOCUMENT_MODEL);

    DocumentModel m;

    if (in.attributes().hasAttribute(XML_SRC))
        return readXml(in.attributes().value(XML_SRC).toString());

    while (in.readNext()
           && !(in.isEndElement() && in.name() == KE::DocumentModel::XML_DOCUMENT_MODEL)) {
        if (in.isStartElement()) {
            if (in.name() == XML_INCLUDE) {
                m.mInclude << in.readElementText();
            } else if (in.name() == XML_EXCLUDE) {
                m.mExclude << in.readElementText();
            } else if (in.name() == XML_PAGE) {
                m.mPageElements << in.readElementText();
            } else if (in.name() == XML_PARAGRAPH) {
                m.mParagraphElements << in.readElementText();
            }
        }
    }

    Q_ASSERT(in.isEndElement() && in.name() == KE::DocumentModel::XML_DOCUMENT_MODEL);
    return m;
}

QString DocumentModel::summary() const
{
    return QString(
               "DocumentModel(Include: %1, Exclude: %2, Page elements: %3, Paragraph elements: %4)")
        .arg(mInclude.join(","),
             mExclude.join(","),
             mPageElements.join(","),
             mParagraphElements.join(","));
}

DocumentModel DocumentModel::readXml(const QString &path)
{
    QFile file(path);
    if (file.open(QFile::ReadOnly)) {
        QXmlStreamReader in(&file);
        in.readNextStartElement();
        return readXml(in);
    }
    throw std::runtime_error("Could not open file for document model.");
}

QStringList DocumentModel::paragraphElements() const
{
    return mParagraphElements;
}

QStringList DocumentModel::pageElements() const
{
    return mPageElements;
}
