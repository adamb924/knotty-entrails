#include "abstractparserlog.h"

AbstractParserLog::AbstractParserLog()
{

}

AbstractParserLog::~AbstractParserLog()
{

}

void AbstractParserLog::printList(const QString &label, const QSet<QList<Parsing> > &list, const WritingSystem &ws) const
{
    if( list.count() > 0 )
    {
        qInfo().noquote() << QObject::tr("-----%1 (%2)-----").arg(label).arg( list.count() );
        QSetIterator<QList<Parsing> > i(list);
        while(i.hasNext())
        {
            QList<Parsing> innerList = i.next();
            if( innerList.count() > 0 )
            {
                qInfo().noquote() << innerList.first().form().text() << qPrintable("\t") << Parsing::parsingListSummary( innerList, ws );
            }
        }
    }
}
