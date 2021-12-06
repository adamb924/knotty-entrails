#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include "abstracttextsegment.h"
#include "abstracttextitem.h"

class KNOTTYENTRAILS_EXPORT TextSegment : public AbstractTextSegment
{
public:
    TextSegment();
    TextSegment(const Form & string);
    ~TextSegment();

    AbstractTextItem *item(int n) const;

    int count() const;

    void addItem( AbstractTextItem * item );

private:
    void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement);

    QList<AbstractTextItem*> mItems;
};

#endif // TEXTSEGMENT_H
