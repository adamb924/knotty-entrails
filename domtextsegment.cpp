#include "domtextsegment.h"

#include "textitem.h"

DomTextSegment::DomTextSegment(QDomDocument *document, const Morphology *morphology) : mDocument(document), mMorphology(morphology)
{
    Q_ASSERT(mMorphology != nullptr);

}

DomTextSegment::~DomTextSegment()
{
    qDeleteAll(mTextItems);
}

AbstractTextItem *DomTextSegment::item(int n) const
{
    return mTextItems[n];
}

int DomTextSegment::count() const
{
    return mTextItems.count();
}

void DomTextSegment::addItem(AbstractTextItem *item)
{
    mTextItems << dynamic_cast<DomTextItem*>(item);
}

void DomTextSegment::doReplacement(int startingPosition, int numberToRemove, QList<AbstractTextItem *> replacement)
{
    /// 3. remove all of the nodes from the segment except the first
    for(int i=startingPosition+numberToRemove-1; i > startingPosition; i--)
    {
        DomTextItem * item = dynamic_cast<DomTextItem *>( mTextItems.at(i) );
        QDomNode node = item->element();
        node.parentNode().removeChild( node );
        mTextItems.removeOne( item );
    }

    /// 4. Prepare replacement
    QDomDocumentFragment replacementFragment = mDocument->createDocumentFragment();
    for(int i=0; i < replacement.count(); i++)
    {
        replacementFragment.appendChild( replacement.at(i)->toElement( mDocument ) );
        /// add a whitespace node if there's another replacement coming up
        /// TODO should this be customizable?
        if( (i+1) < replacement.count() ) /// i.e., hasNext()
        {
            QDomElement whitespace = mDocument->createElement("whitespace");
            whitespace.appendChild( mDocument->createTextNode(" ") );
            replacementFragment.appendChild( whitespace);
        }
    }

    /// 5. Replace the first node with the replacement fragment
    DomTextItem * firstItem = mTextItems.at(startingPosition);
    QDomNode firstNode = firstItem->element();

    /// just delete the first node if there's no replacement
    if( replacement.isEmpty() )
    {
        firstNode.parentNode().removeChild( firstNode );
        mTextItems.removeOne( firstItem );
    }
    /// otherwise replace it with the replacement fragment
    else
    {
        /// it turns out that we need to modify the DOM document first
        /// so that the document elements are parented properly
        /// when we store them in mTextItems

        int index = mTextItems.indexOf( firstItem );
        Q_ASSERT( index != -1 );
        mTextItems.removeOne( firstItem );
        for(int i=0; i<replacementFragment.childNodes().count(); i++)
        {
            QDomElement element = replacementFragment.childNodes().at(i).toElement();
            mTextItems.insert( index + i, new DomTextItem(element, mMorphology) );
        }

        QDomNode returnedNode = firstNode.parentNode().replaceChild( replacementFragment, firstNode );
        if( returnedNode.isNull() )
            qCritical() << "DomTextSegment::replace Unable to replace child node.";
    }
}
