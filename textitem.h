#ifndef TEXTITEM_H
#define TEXTITEM_H

#include "knotty-entrails_global.h"
#include "datatypes/parsing.h"
#include "abstracttextitem.h"
#include "parsedform.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT TextItem : public AbstractTextItem
{
public:
    explicit TextItem(Type type = TextItem::Simple );
    explicit TextItem(const ME::Form & output, Type type = TextItem::Simple );
    ~TextItem() override;

    AbstractParsedForm &input() override;
    AbstractParsedForm &output() override;
    const AbstractParsedForm &input() const override;
    const AbstractParsedForm &output() const override;

    Type type() const override;
    QString typeString() const;

    bool modifiable() const override;
    void setModifiable(bool modifiable) override;

protected:
    ParsedForm mInput;
    ParsedForm mOutput;
    QString mGlossaryKey;
    Type mType;
    bool mModifiable;
    QString mSource;
    ME::Parsing mSelectedParsing;
    QString mParsingSummary;
    QString mParsingIdentifier;
};

} // namespace KE

#endif // TEXTITEM_H
