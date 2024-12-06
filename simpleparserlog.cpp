#include "simpleparserlog.h"

using namespace KE;

SimpleParserLog::SimpleParserLog()
{

}

void SimpleParserLog::addAmbiguousParsing(const QList<ME::Parsing> &parsings)
{
    mAmbiguousParsings.insert( parsings );
}

void SimpleParserLog::printReport(const ME::WritingSystem &ws) const
{
    printList(QObject::tr("Ambiguous Parsings"), mAmbiguousParsings, ws);
}
