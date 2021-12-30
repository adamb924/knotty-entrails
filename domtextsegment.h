#ifndef DOMTEXTSEGMENT_H
#define DOMTEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include "abstracttextsegment.h"
#include "domtextitem.h"

class KNOTTYENTRAILS_EXPORT DomTextSegment : public AbstractTextSegment
{
public:
    DomTextSegment(QDomDocument *document, const Morphology *morphology);
    ~DomTextSegment() override;

    AbstractTextItem *item(int n) const override;

    int count() const override;

    void addItem( AbstractTextItem * item ) override;

private:
    void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement) override;

    QDomDocument *mDocument;
    const Morphology *mMorphology;
    QList<DomTextItem*> mTextItems;
};

#endif // DOMTEXTSEGMENT_H
