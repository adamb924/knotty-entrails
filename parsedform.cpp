#include "parsedform.h"

ParsedForm::ParsedForm()
{

}

ParsedForm::ParsedForm(const Form &form) : mForm(form)
{
}

ParsedForm::ParsedForm(const Parsing &parsing, const WritingSystem &summaryWs) : mForm(parsing.form())
{
    /// setParsing does a lot of other things
    setParsing( parsing, summaryWs );
}

ParsedForm::~ParsedForm()
{

}

Form ParsedForm::form() const
{
    return mForm;
}

void ParsedForm::setForm(const Form &form)
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

Parsing ParsedForm::parsing()
{
    return mSelectedParsing;
}

void ParsedForm::setParsing(const Parsing &p, const WritingSystem &summaryWs)
{
    mSelectedParsing = p;
    if( ! p.isNull() )
    {
        mWellFormedness = AbstractTextItem::WellformedUnknown;
    }

    /// set the parsing identifier
    setParsingIdentifier( p.labelSummary() );
    setParsingSummary( p.interlinearStyleSummary(summaryWs) );
}

QString ParsedForm::parsingSummary() const
{
    return mParsingSummary;
}

QString ParsedForm::parsingIdentifier() const
{
    return mParsingIdentifier;
}

void ParsedForm::setParsingIdentifier(const QString &identifier)
{
    mParsingIdentifier = identifier;
}

void ParsedForm::setParsingSummary(const QString &summary)
{
    mParsingSummary = summary;
}
