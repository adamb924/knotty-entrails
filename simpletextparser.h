#ifndef SIMPLETEXTPARSER_H
#define SIMPLETEXTPARSER_H

#include "knotty-entrails_global.h"

#include "abstracttextparser.h"

namespace KE {

class ParserLog;

class KNOTTYENTRAILS_EXPORT SimpleTextParser : public AbstractTextParser
{
public:
    explicit SimpleTextParser(const ME::Morphology *morphology);

    void parseText( AbstractTextAdapter * text, WhichForm which, AbstractParserLog * log = nullptr) const override;

private:
    const ME::Morphology * mMorphology;
};

} // namespace KE

#endif // SIMPLETEXTPARSER_H
