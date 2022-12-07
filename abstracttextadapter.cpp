#include "abstracttextadapter.h"

#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include <QtDebug>
#include <QRegularExpression>

#include "morphology.h"
#include "abstracttextitem.h"
#include "abstracttextsegment.h"
#include "abstractparsedform.h"

AbstractTextAdapter::AbstractTextAdapter(const Morphology *morphology) : mDomDocument(nullptr), mMorphology(morphology)
{

}

AbstractTextAdapter::~AbstractTextAdapter()
{
    if( mDomDocument != nullptr )
        delete  mDomDocument;
}

QDomDocument *AbstractTextAdapter::domDocument() const
{
    return mDomDocument;
}

void AbstractTextAdapter::save(const QString &newFilename) const
{
    QFile file(newFilename);
    if( file.open( QFile::WriteOnly ) )
    {
        QTextStream out(&file);

        #if QT_VERSION >= 0x060000
            out.setEncoding(QStringConverter::Utf8);
        #else
            out.setCodec("UTF-8");
        #endif

        out << mDomDocument->toString();
        file.close();
    }
    else
    {
        qCritical() << "Could not open for reading: " << newFilename;
    }
}

void AbstractTextAdapter::dumpToDebug() const
{
    for(int i=0; i<count(); i++)
    {
        const AbstractTextSegment * seg = segment(i);
        for(int j=0; j<seg->count();j++)
        {
            qDebug().noquote() << QString("<%1,%2>").arg(i).arg(j) << seg->item(j)->input().form().summary() << seg->item(j)->output().form().summary();
        }
    }
}

void AbstractTextAdapter::foreachTextItem(std::function<void(AbstractTextItem*)> funct)
{
    for(int i=0; i<count(); i++)
    {
        segment(i)->foreachTextItem(funct);
    }
}
