#include "simpleparserlog.h"

SimpleParserLog::SimpleParserLog()
{

}

void SimpleParserLog::addAmbiguousParsing(const QList<Parsing> &parsings)
{
    mAmbiguousParsings.insert( parsings );
}

void SimpleParserLog::printReport(const WritingSystem &ws) const
{
    printList(QObject::tr("Ambiguous Parsings"), mAmbiguousParsings, ws);
}
