#ifndef DOMTEXTSEGMENT_H
#define DOMTEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include "abstracttextsegment.h"
#include "domtextitem.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT DomTextSegment : public AbstractTextSegment
{
public:
    DomTextSegment(QDomDocument *document, const ME::Morphology *morphology);
    ~DomTextSegment() override;

    AbstractTextItem *item(int n) const override;

    int count() const override;

    void addItem( AbstractTextItem * item ) override;

private:
    void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement) override;

    QDomDocument *mDocument;
    const ME::Morphology *mMorphology;
    QList<DomTextItem*> mTextItems;
};

} // namespace KE

#endif // DOMTEXTSEGMENT_H
