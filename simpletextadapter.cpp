#include "simpletextadapter.h"

#include <QDomDocument>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlInputSource>
#include <QXmlSimpleReader>

#include "domtextsegment.h"
#include "domtextitem.h"

SimpleTextAdapter::SimpleTextAdapter(const QString &filename, const Morphology *morphology) : AbstractTextAdapter(morphology), mFilename(filename)
{
    Q_ASSERT(mMorphology != nullptr);
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        QXmlInputSource source;
        source.setData(in.readAll());
        QXmlSimpleReader reader;
        mDomDocument = new QDomDocument;
        mDomDocument->setContent(&source, &reader);

        mTheTextSegment = new DomTextSegment(mDomDocument, mMorphology);

        file.close();

        loadTextSegmentFromElement( mDomDocument->documentElement() );
    }
    else
    {
        qWarning() << "SimpleTextAdapter::SimpleTextAdapter opening failed:" << filename;
    }
}

SimpleTextAdapter::SimpleTextAdapter(QDomElement element, const Morphology *morphology) : AbstractTextAdapter(morphology)
{
    mDomDocument = new QDomDocument( element.ownerDocument() );
    mTheTextSegment = new DomTextSegment(mDomDocument, mMorphology);
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
        mTheTextSegment->addItem( new DomTextItem( output, mMorphology ) );
    }
}
