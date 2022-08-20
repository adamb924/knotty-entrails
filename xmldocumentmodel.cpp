#include "xmldocumentmodel.h"

#include <QFile>
#include <QtDebug>

XmlDocumentModel::XmlDocumentModel()
{

}

QString XmlDocumentModel::label() const
{
    return mLabel;
}

void XmlDocumentModel::setLabel(const QString &label)
{
    mLabel = label;
}

XmlDocumentModel XmlDocumentModel::readFromXml(QXmlStreamReader &in)
{
    Q_ASSERT( in.name().toString() == XML_DOCUMENT_MODEL );

    /// follow the src attribute to a filename if there is one
    if( in.attributes().hasAttribute("src") )
    {
        XmlDocumentModel model = readFromXml( in.attributes().value("src").toString() );
        while( !in.atEnd() && !(in.isEndElement() && in.name() == XML_DOCUMENT_MODEL) )
            in.readNext();
        return model;
    }

    XmlDocumentModel model;
    model.setLabel( in.attributes().value( XML_DOCUMENT_LABEL ).toString() );

    in.readNextStartElement();
    Q_ASSERT( in.name().toString() == XML_DOCUMENT_LEVEL );

    model.mRoot = XmlDocumentModelLevel::readFromXml(in);

    return model;
}

XmlDocumentModel XmlDocumentModel::readFromXml(const QString &path)
{
    QFile file(path);
    if( file.open( QFile::ReadOnly ) )
    {
        QXmlStreamReader in(&file);
        in.readNextStartElement();
        return readFromXml(in);
    }
    else
    {
        std::string message = "Can't open file: ";
        message += path.toUtf8().constData();
        throw std::runtime_error( message );
    }
}

QString XmlDocumentModel::summary() const
{
    return "XmlDocumentModel(" + mLabel + ") { " + mRoot.summary() + " }";
}

const XmlDocumentModelLevel &XmlDocumentModel::root() const
{
    return mRoot;
}

QList<QDomNode> XmlDocumentModel::getRootDivisions(QDomDocument document)
{
    return mRoot.matchingChildren( document );
}

QList<QDomNode> XmlDocumentModel::getMajorDivisions(QDomDocument document)
{
    QList<QDomNode> majorDivisions;
    QList<QDomNode> roots = getRootDivisions(document);
    for(int i=0; i<roots.length(); i++)
    {
        for(int j=0; j<mRoot.children().count(); j++)
        {
            majorDivisions.append( mRoot.children().at(j).matchingChildren( roots.at(i) ) );
        }
    }
    return majorDivisions;
}
