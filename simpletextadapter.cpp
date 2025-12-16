#include "simpletextadapter.h"

#include <QDomDocument>
#include <QFile>
#include <QXmlStreamReader>

#include "domtextsegment.h"
#include "domtextitem.h"

using namespace KE;

SimpleTextAdapter::SimpleTextAdapter(const QString &filename, const ME::Morphology *morphology) : AbstractTextAdapter(morphology), mFilename(filename)
{
    Q_ASSERT(mMorphology != nullptr);
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader xml(&file);
        mDomDocument = new QDomDocument;
        mDomDocument->setContent(&xml, QDomDocument::ParseOption::PreserveSpacingOnlyNodes);

        mTheTextSegment = new DomTextSegment(mDomDocument, this);

        file.close();

        loadTextSegmentFromElement( mDomDocument->documentElement() );
    }
    else
    {
        qWarning() << "SimpleTextAdapter::SimpleTextAdapter opening failed:" << filename;
    }
}

SimpleTextAdapter::SimpleTextAdapter(QDomElement element, const ME::Morphology *morphology) : AbstractTextAdapter(morphology)
{
    mDomDocument = new QDomDocument( element.ownerDocument() );
    mTheTextSegment = new DomTextSegment(mDomDocument, this);
    loadTextSegmentFromElement( element );
}

SimpleTextAdapter::~SimpleTextAdapter()
{

}

int SimpleTextAdapter::count() const
{
    return 1;
}

AbstractTextSegment *SimpleTextAdapter::segment(int n)
{
    Q_UNUSED(n)
    return mTheTextSegment;
}

const AbstractTextSegment *SimpleTextAdapter::segment(int n) const
{
    Q_UNUSED(n)
    return mTheTextSegment;
}

QString SimpleTextAdapter::filename() const
{
    return mFilename;
}

void SimpleTextAdapter::loadTextSegmentFromElement(QDomElement element)
{
    QDomNodeList outputList = element.elementsByTagName("text-item");
    for (int i = 0; i < outputList.count(); i++)
    {
        QDomElement output = outputList.at(i).toElement();
        mTheTextSegment->addItem( new DomTextItem( output, this ) );
    }
}
