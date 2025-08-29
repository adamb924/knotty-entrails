#ifndef SIMPLETEXTPARSER_H
#define SIMPLETEXTPARSER_H

#include "knotty-entrails_global.h"

#include "abstracttextparser.h"

namespace KE {

class ParserLog;

class KNOTTYENTRAILS_EXPORT SimpleTextParser : public AbstractTextParser
{
public:
    explicit SimpleTextParser();

    void parseText(const ME::Morphology *morphology, AbstractTextAdapter * text, WhichForm which, AbstractParserLog * log = nullptr) const override;
};

} // namespace KE

#endif // SIMPLETEXTPARSER_H
