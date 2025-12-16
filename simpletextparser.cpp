#include "simpletextparser.h"

#include "morphology.h"
#include "abstracttextadapter.h"
#include "abstractparsedform.h"
#include "abstractparserlog.h"

using namespace KE;

SimpleTextParser::SimpleTextParser()
{

}

void SimpleTextParser::parseText(const ME::Morphology *morphology, AbstractTextAdapter *text, WhichForm which, AbstractParserLog *log) const
{
    text->foreachTextItem( [this,which,log,morphology](AbstractTextItem * item) {
        /// get possible parsings
        QList<ME::Parsing> ps = morphology->possibleParsings((*(item).*which)().form());
        /// set the wellformedness
        (*(item).*which)().setWellformedness( ps.count() );
        /// if a parsing is available, use it
        if( ps.count() > 0 )
        {
            (*(item).*which)().setParsing( ps.first() );
        }
        else /// otherwise set the parsing to a null value
        {
            (*(item).*which)().setParsing( ME::Parsing() );
        }
        /// if there are multiple parsings, and there is a log, log the ambiguity
        if( ps.count() > 1 && log != nullptr )
        {
            log->addAmbiguousParsing( ps );
        }
    } );
}
