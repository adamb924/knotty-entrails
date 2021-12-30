#ifndef ABSTRACTTEXTPARSER_H
#define ABSTRACTTEXTPARSER_H

#include "knotty-entrails_global.h"

class AbstractTextAdapter;
class AbstractParserLog;
#include "abstracttextitem.h"

typedef AbstractParsedForm& (AbstractTextItem::*WhichForm)();

class KNOTTYENTRAILS_EXPORT AbstractTextParser
{
public:
    AbstractTextParser();
    AbstractTextParser(std::function<Form(Form)> normalizationFunction);
    virtual ~AbstractTextParser();

    virtual void parseText( AbstractTextAdapter * text, WhichForm which, AbstractParserLog * log = nullptr) const = 0;

protected:
    std::function<Form(Form)> mNormalizationFunction;
};

#endif // ABSTRACTTEXTPARSER_H
