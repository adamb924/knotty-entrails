#ifndef DOMPARSEDFORM_H
#define DOMPARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstractparsedform.h"

#include <QDomElement>

class KNOTTYENTRAILS_EXPORT DomParsedForm : public AbstractParsedForm
{
public:
    DomParsedForm(const QDomElement & textItem, const Morphology * morphology);
    ~DomParsedForm();

    Form form() const;
    void setForm( const Form & form );

    AbstractTextItem::WellformednessStatus wellformedness() const;
    void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness);

    QString glossaryKey() const;
    void setGlossaryKey(const QString &glossaryKey);

    QString source() const;
    void setSource(const QString & source);

    Parsing parsing();
    void setParsing(const Parsing & p);

    QString parsingIdentifier() const;

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
    void setParsingIdentifier(const QString & identifier);

private:
    void ensureElementExists(QDomElement &element, const QString & elementName);

    QDomElement mParsedFormElement, mFormElement;
    const Morphology * mMorphology;
    Parsing mCachedParsing;
};

#endif // DOMPARSEDFORM_H
