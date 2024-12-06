#include "parsedform.h"

#include "morphology.h"

using namespace KE;

ParsedForm::ParsedForm() : mWellFormedness(AbstractTextItem::Untested)
{

}

ParsedForm::ParsedForm(const ME::Form &form) : mForm(form), mWellFormedness(AbstractTextItem::Untested)
{
}

ParsedForm::ParsedForm(const ME::Parsing &parsing) : mForm(parsing.form()), mWellFormedness(AbstractTextItem::Untested)
{
    /// setParsing does a lot of other things
    ParsedForm::setParsing( parsing );
}

ParsedForm::~ParsedForm()
{

}

ME::Form ParsedForm::form() const
{
    return mForm;
}

void ParsedForm::setForm(const ME::Form &form)
{
    mForm = form;
}

AbstractTextItem::WellformednessStatus ParsedForm::wellformedness() const
{
    return mWellFormedness;
}

void ParsedForm::setWellformedness(AbstractTextItem::WellformednessStatus wellformedness)
{
    mWellFormedness = wellformedness;
}

QString ParsedForm::glossaryKey() const
{
    return mGlossaryKey;
}

void ParsedForm::setGlossaryKey(const QString &glossaryKey)
{
    mGlossaryKey = glossaryKey;
}

QString ParsedForm::source() const
{
    return mSource;
}

void ParsedForm::setSource(const QString &source)
{
    mSource = source;
}

ME::Parsing ParsedForm::parsing()
{
    return mSelectedParsing;
}

void ParsedForm::setParsing(const ME::Parsing &p)
{
    mSelectedParsing = p;
    if( ! p.isNull() )
    {
        mWellFormedness = AbstractTextItem::WellformedUnknown;
    }

    /// set the parsing identifier
    setParsingIdentifier( p.labelSummary() );
}

QString ParsedForm::parsingIdentifier() const
{
    return mParsingIdentifier;
}

void ParsedForm::setParsingIdentifier(const QString &identifier)
{
    mParsingIdentifier = identifier;
}
