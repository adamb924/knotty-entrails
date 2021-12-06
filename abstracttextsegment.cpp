#include "abstracttextsegment.h"

#include "abstracttextitem.h"
#include "abstractparsedform.h"

#include "textitem.h"

AbstractTextSegment::AbstractTextSegment()
{

}

AbstractTextSegment::~AbstractTextSegment()
{
}

int AbstractTextSegment::replace(int from, int numberToRemove, QList<AbstractTextItem *> withItems)
{
    const int replacementLength = qMax( numberToRemove, withItems.count() );

    /// 1. Add nodes with withItems until it's as long as replacementLength
    for(int i=withItems.length(); i < replacementLength; i++)
    {
        withItems << new TextItem(TextItem::Translated);
    }

    /// 2. Store all of the inputs in withItems
    /// this should be count, because count is the number
    /// of input values that we have
    for(int i=0; i < numberToRemove; i++)
    {
        withItems.at(i)->input().setForm( item(from+i)->input().form() );
        withItems.at(i)->setModifiable(false);
    }

//    for(int i=0; i < count(); i++)
//    {
//        qDebug() << "AbstractTextSegment::replace BEFORE" << item(i)->input().form().summary() << item(i)->output().form().summary();
//    }

    doReplacement( from, numberToRemove, withItems );

//    for(int i=0; i < count(); i++)
//    {
//        qDebug() << "AbstractTextSegment::replace AFTER" << item(i)->input().form().summary() << item(i)->output().form().summary();
//    }

    return from + withItems.count() - 1;
}

Form AbstractTextSegment::outputsToForm() const
{
    if( count() == 0 )
    {
        return Form();
    }
    Form f( item(0)->output().form().writingSystem(), "" );
    for( int i=0; i < count(); i++ )
    {
        f += item(i)->output().form();
        if( i < (count() - 1) )
        {
            f+= " ";
        }
    }
    return f;
}

QString AbstractTextSegment::summary() const
{
    QString dbgString;
    QTextStream dbg(&dbgString);

    dbg << "--- AbstractTextSegment ---\n";
    for(int i=0; i<count(); i++)
    {
        dbg << i << ": " << item(i)->summary() << "\n";
    }
    dbg << "---------------------------\n";

    return dbgString;
}

void AbstractTextSegment::foreachTextItem(std::function<void(AbstractTextItem*)> funct)
{
    for(int i=0; i<count(); i++)
    {
        funct( item(i) );
    }
}
