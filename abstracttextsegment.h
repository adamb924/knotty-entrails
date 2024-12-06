#ifndef ABSTRACTTEXTSEGMENT_H
#define ABSTRACTTEXTSEGMENT_H

#include "knotty-entrails_global.h"

#include <QList>

#include "datatypes/form.h"

namespace KE {

class AbstractTextItem;

class KNOTTYENTRAILS_EXPORT AbstractTextSegment
{
public:
    AbstractTextSegment();
    virtual ~AbstractTextSegment();

    virtual AbstractTextItem *item(int n) const = 0;

    virtual int count() const = 0;

    virtual void addItem( AbstractTextItem * item ) = 0;

    int replace(int from, int numberToRemove, QList<AbstractTextItem*> withItems);

    ME::Form outputsToForm() const;

    QString summary() const;

    void foreachTextItem(std::function<void(AbstractTextItem*)> funct);

private:
    virtual void doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem*> replacement) = 0;
};

} // namespace KE

#endif // ABSTRACTTEXTSEGMENT_H
