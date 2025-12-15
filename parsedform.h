#ifndef PARSEDFORM_H
#define PARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstractparsedform.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT ParsedForm : public AbstractParsedForm
{
public:
    ParsedForm();
    explicit ParsedForm(const ME::Form & form);
    ~ParsedForm() override;

    ME::Form form() const override;
    void setForm( const ME::Form & form ) override;

    AbstractTextItem::WellformednessStatus wellformedness() const override;
    void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness) override;

    QString glossaryKey() const override;
    void setGlossaryKey(const QString &glossaryKey) override;

    QString source() const override;
    void setSource(const QString & source) override;

    ME::Parsing parsing() override;
    void setParsing(const ME::Parsing & p) override;

    QString parsingIdentifier() const override;

protected:
    void setParsingIdentifier(const QString & identifier) override;

private:
    ME::Form mForm;
    QString mGlossaryKey;
    AbstractTextItem::WellformednessStatus mWellFormedness;
    QString mSource;
    ME::Parsing mSelectedParsing;
    QString mParsingIdentifier;
};

} // namespace KE

#endif // PARSEDFORM_H
