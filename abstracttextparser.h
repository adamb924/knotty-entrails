#ifndef ABSTRACTTEXTPARSER_H
#define ABSTRACTTEXTPARSER_H

#include "knotty-entrails_global.h"
#include "abstracttextitem.h"

namespace KE {

class AbstractTextAdapter;
class AbstractParserLog;

typedef AbstractParsedForm& (AbstractTextItem::*WhichForm)();

class KNOTTYENTRAILS_EXPORT AbstractTextParser
{
public:
    AbstractTextParser();
    AbstractTextParser(std::function<ME::Form(ME::Form)> normalizationFunction);
    virtual ~AbstractTextParser();

    virtual void parseText(const ME::Morphology *morphology, AbstractTextAdapter * text, WhichForm which, AbstractParserLog * log = nullptr) const = 0;

protected:
    std::function<ME::Form(ME::Form)> mNormalizationFunction;
};

} // namespace KE

#endif // ABSTRACTTEXTPARSER_H
