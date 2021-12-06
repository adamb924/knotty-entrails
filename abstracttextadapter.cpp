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
#include "textsegment.h"

AbstractTextAdapter::AbstractTextAdapter(const Morphology *morphology) : mMorphology(morphology)
{

}

AbstractTextAdapter::~AbstractTextAdapter()
{
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
        out.setCodec("UTF-8");
        out << mDomDocument->toString();
        file.close();
    }
    else
    {
        qCritical() << "Could not open for reading: " << newFilename;
    }
}

void AbstractTextAdapter::replaceOutput(const Form &replaceThis, const Form &withThis)
{
    if( mMorphology != nullptr )
    {
        bool changed = false;

        for(int i=0; i<count(); i++)
        {
            for(int j=0; j < segment(i)->count(); j++ )
            {
                AbstractTextItem * item = segment(i)->item(j);
                if( item->output().form() == replaceThis )
                {
                    item->output().setForm( withThis );
                    item->output().setWellformednessFromMorphology( mMorphology );
                    changed = true;
                }
            }
        }

        /// only emit once per replacement operation
        if( changed )
        {
            emit formChanged(replaceThis, withThis);
        }
    }
}

void AbstractTextAdapter::searchAndReplace(const Form &replaceThis, const Form &withThis)
{
    if( mMorphology != nullptr )
    {
        QSet<QPair<Form,Form>> changedForms;

        QRegularExpression re( replaceThis.text() );
        if( ! re.isValid() )
        {
            qWarning() << "Invalid regular expression:" << replaceThis.text();
            return;
        }
        for(int i=0; i<count(); i++)
        {
            for(int j=0; j < segment(i)->count(); j++ )
            {
                AbstractTextItem * item = segment(i)->item(j);
                if( item->output().form().writingSystem() == replaceThis.writingSystem() )
                {
                    const Form previous = item->output().form();
                    QString s = previous.text();
                    s.replace( re, withThis.text() );

                    if( s != item->output().form().text() )
                    {
                        const Form f( withThis.writingSystem(), s );
                        item->output().setForm( f );
                        item->output().setWellformednessFromMorphology( mMorphology );

                        changedForms.insert( QPair<Form,Form>( previous, f) );
                    }
                }
            }
        }

        /// only emit a signal once per replacement operation, but emit it for each changed form
        QSetIterator<QPair<Form,Form>> i(changedForms);
        while( i.hasNext() )
        {
            QPair<Form,Form> pair = i.next();
            emit formChanged( pair.first, pair.second );
        }
    }
}

void AbstractTextAdapter::selectOutputParsing(const Form &f, const Parsing &p, const WritingSystem & summaryWs)
{
    bool changed = false;

    for(int i=0; i<count(); i++)
    {
        for(int j=0; j < segment(i)->count(); j++ )
        {
            AbstractTextItem * item = segment(i)->item(j);
            if( item->modifiable() && item->output().form() == f )
            {
                item->output().setParsing(p, summaryWs);
                item->setModifiable(false);
                changed = true;
            }
        }
    }

    /// only emit once per replacement operation
    if( changed )
    {
        emit formChanged(f,f);
    }
}

void AbstractTextAdapter::reparseOutputs(const WritingSystem & summaryWs)
{
    for(int i=0; i<count(); i++)
    {
        for(int j=0; j < segment(i)->count(); j++ )
        {
            QList<Parsing> ps = mMorphology->possibleParsings( segment(i)->item(j)->output().form() );
            segment(i)->item(j)->output().setWellformedness(ps.count());
            segment(i)->item(j)->output().setParsing( ps.first(), summaryWs );
        }
    }
}

void AbstractTextAdapter::setGrammaticalityForOutputs(bool ungrammaticalOnly)
{
    for(int i=0; i<count(); i++)
    {
        for(int j=0; j < segment(i)->count(); j++ )
        {
            if( ! ungrammaticalOnly || ! segment(i)->item(j)->output().isWellformed() )
            {
                segment(i)->item(j)->output().setWellformednessFromMorphology(mMorphology);
            }
        }
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
