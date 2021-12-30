#ifndef PARSEDFORM_H
#define PARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstractparsedform.h"

class KNOTTYENTRAILS_EXPORT ParsedForm : public AbstractParsedForm
{
public:
    ParsedForm();
    explicit ParsedForm(const Form & form);
    explicit ParsedForm(const Parsing & parsing);
    ~ParsedForm() override;

    Form form() const override;
    void setForm( const Form & form ) override;

    AbstractTextItem::WellformednessStatus wellformedness() const override;
    void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness) override;

    QString glossaryKey() const override;
    void setGlossaryKey(const QString &glossaryKey) override;

    QString source() const override;
    void setSource(const QString & source) override;

    Parsing parsing() override;
    void setParsing(const Parsing & p) override;

    QString parsingIdentifier() const override;

protected:
    void setParsingIdentifier(const QString & identifier) override;

private:
    Form mForm;
    QString mGlossaryKey;
    AbstractTextItem::WellformednessStatus mWellFormedness;
    QString mSource;
    Parsing mSelectedParsing;
    QString mParsingIdentifier;
};

#endif // PARSEDFORM_H
