#ifndef DOMPARSEDFORM_H
#define DOMPARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstractparsedform.h"

#include <QDomElement>

namespace KE {

class KNOTTYENTRAILS_EXPORT DomParsedForm : public AbstractParsedForm
{
public:
    DomParsedForm(const QDomElement & textItem, const ME::Morphology * morphology);
    ~DomParsedForm() override;

    ME::Form form() const override;
    void setForm(const ME::Form & form) override;

    AbstractTextItem::WellformednessStatus wellformedness() const override;
    void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness) override;

    QString glossaryKey() const override;
    void setGlossaryKey(const QString &glossaryKey) override;

    QString source() const override;
    void setSource(const QString & source) override;

    ME::Parsing parsing() override;
    void setParsing(const ME::Parsing & p) override;

    QString parsingIdentifier() const override;

    /// XML Names
    static QString XML_ID;
    static QString XML_LANG;
    static QString XML_FORM;
    static QString XML_WELLFORMED;
    static QString XML_PARSING;
    static QString XML_PARSING_SUMMARY;
    static QString XML_PARSING_IDENTIFIER;
    static QString XML_SOURCE;
    static QString XML_GLOSSARY;

protected:
    void setParsingIdentifier(const QString & identifier) override;

private:
    void ensureElementExists(QDomElement &element, const QString & elementName);

    QDomElement mParsedFormElement, mFormElement;
    const ME::Morphology * mMorphology;
    ME::Parsing mCachedParsing;
};

} // namespace KE

#endif // DOMPARSEDFORM_H
