#ifndef PARSEDFORM_H
#define PARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstractparsedform.h"

class KNOTTYENTRAILS_EXPORT ParsedForm : public AbstractParsedForm
{
public:
    ParsedForm();
    explicit ParsedForm(const Form & form);
    ParsedForm(const Parsing & parsing, const WritingSystem &summaryWs);
    ~ParsedForm();

    Form form() const;
    void setForm( const Form & form );

    AbstractTextItem::WellformednessStatus wellformedness() const;
    void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness);

    QString glossaryKey() const;
    void setGlossaryKey(const QString &glossaryKey);

    QString source() const;
    void setSource(const QString & source);

    Parsing parsing();
    void setParsing(const Parsing & p, const WritingSystem & summaryWs);

    QString parsingSummary() const;
    QString parsingIdentifier() const;

protected:
    void setParsingIdentifier(const QString & identifier);
    void setParsingSummary(const QString & summary);

private:
    Form mForm;
    QString mGlossaryKey;
    AbstractTextItem::WellformednessStatus mWellFormedness;
    QString mSource;
    Parsing mSelectedParsing;
    QString mParsingSummary;
    QString mParsingIdentifier;
};

#endif // PARSEDFORM_H
