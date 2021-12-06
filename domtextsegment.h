#ifndef DOMTEXTSEGMENT_H
#define DOMTEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include "abstracttextsegment.h"
#include "domtextitem.h"

class KNOTTYENTRAILS_EXPORT DomTextSegment : public AbstractTextSegment
{
public:
    DomTextSegment(QDomDocument *document, const Morphology *morphology);
    ~DomTextSegment();

    AbstractTextItem *item(int n) const;

    int count() const;

    void addItem( AbstractTextItem * item );

private:
    void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement);

    QDomDocument *mDocument;
    const Morphology *mMorphology;
    QList<DomTextItem*> mTextItems;
};

#endif // DOMTEXTSEGMENT_H
