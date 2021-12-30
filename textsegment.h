#ifndef TEXTSEGMENT_H
#define TEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include "abstracttextsegment.h"
#include "abstracttextitem.h"

class KNOTTYENTRAILS_EXPORT TextSegment : public AbstractTextSegment
{
public:
    TextSegment();
    explicit TextSegment(const Form & string);
    ~TextSegment() override;

    AbstractTextItem *item(int n) const override;

    int count() const override;

    void addItem( AbstractTextItem * item ) override;

private:
    void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement) override;

    QList<AbstractTextItem*> mItems;
};

#endif // TEXTSEGMENT_H
