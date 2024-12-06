#include "abstractparserlog.h"

using namespace KE;

AbstractParserLog::AbstractParserLog()
{

}

AbstractParserLog::~AbstractParserLog()
{

}

void AbstractParserLog::printList(const QString &label, const QSet<QList<ME::Parsing> > &list, const ME::WritingSystem &ws) const
{
    if( list.count() > 0 )
    {
        qInfo().noquote() << QObject::tr("-----%1 (%2)-----").arg(label).arg( list.count() );
        QSetIterator<QList<ME::Parsing> > i(list);
        while(i.hasNext())
        {
            QList<ME::Parsing> innerList = i.next();
            if( innerList.count() > 0 )
            {
                qInfo().noquote() << innerList.first().form().text() << qPrintable("\t") << ME::Parsing::parsingListSummary( innerList, ws );
            }
        }
    }
}
