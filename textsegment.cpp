#include "textsegment.h"

#include "textitem.h"

#include <QRegularExpression>

using namespace KE;

TextSegment::TextSegment()
{

}

TextSegment::TextSegment(const ME::Form &string)
{
    QStringList strings = string.text().split(QRegularExpression("\\b", QRegularExpression::UseUnicodePropertiesOption), Qt::SkipEmptyParts );
    QStringList tokens;
    for(int i=0; i<strings.count(); i++)
    {
        if( ! strings.at(i).trimmed().isEmpty() )
        {
            tokens << strings.at(i);
        }

        if( (i+2) < strings.count() ) /// if there are at least two remaining tokens
        {
            if( strings.at(i+1) == "-" )
            {
                tokens.last() = strings.at(i) + strings.at(i+1) + strings.at(i+2);
                i += 2;
            }
        }
    }
    foreach(QString s, tokens)
    {
        TextItem * item = new TextItem( AbstractTextItem::Translated );
        item->input().setForm( ME::Form( string.writingSystem(), s ) );
        addItem( item );
    }
}

TextSegment::~TextSegment()
{
    qDeleteAll(mItems);
}

AbstractTextItem *TextSegment::item(int n) const
{
    return mItems.at(n);
}

int TextSegment::count() const
{
    return mItems.count();
}

void TextSegment::addItem(AbstractTextItem *item)
{
    mItems << item;
}

void TextSegment::doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem *> replacement)
{
    /// remove old items
    for(int i=0; i<numberToRemove; i++)
    {
        mItems.removeAt( startingPosition );
    }
    /// add the new items
    for(int i=0; i<replacement.count(); i++)
    {
        mItems.insert( startingPosition+i, replacement.at(i) );
    }
}
