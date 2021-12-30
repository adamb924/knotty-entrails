#ifndef SIMPLETEXTPARSER_H
#define SIMPLETEXTPARSER_H

#include "knotty-entrails_global.h"

#include "abstracttextparser.h"

class ParserLog;

class KNOTTYENTRAILS_EXPORT SimpleTextParser : public AbstractTextParser
{
public:
    SimpleTextParser(const Morphology *morphology);

    void parseText( AbstractTextAdapter * text, WhichForm which, AbstractParserLog * log = nullptr) const;

private:
    const Morphology * mMorphology;
};

#endif // SIMPLETEXTPARSER_H
