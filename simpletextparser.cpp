#include "simpletextparser.h"

#include "morphology.h"
#include "abstracttextadapter.h"
#include "abstractparsedform.h"
#include "abstractparserlog.h"

SimpleTextParser::SimpleTextParser(const Morphology * morphology) : mMorphology(morphology)
{

}

void SimpleTextParser::parseText(AbstractTextAdapter *text, WhichForm which, AbstractParserLog *log) const
{
    text->foreachTextItem( [this,which,log](AbstractTextItem * item) {
        /// get possible parsings
        QList<Parsing> ps = mMorphology->possibleParsings( mNormalizationFunction( (*(item).*which)().form() ) );
        /// if a parsing is available, use it
        if( ps.count() > 0 )
        {
            (*(item).*which)().setParsing( ps.first() );
        }
        else /// otherwise set the parsing to a null value
        {
            (*(item).*which)().setParsing( Parsing() );
        }
        /// if there are multiple parsings, and there is a log, log the ambiguity
        if( ps.count() > 1 && log != nullptr )
        {
            log->addAmbiguousParsing( ps );
        }
    } );
}
