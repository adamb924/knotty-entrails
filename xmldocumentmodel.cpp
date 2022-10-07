#include "xmldocumentmodel.h"

#include <QFile>
#include <QtDebug>
#include <stdexcept>

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

XmlDocumentPosition XmlDocumentModel::getRootPosition(QDomDocument document) const
{
    QList<XmlDocumentPosition> positions;
    for(int i=0; i< mRoot.elementNames().count(); i++)
    {
        QDomNodeList nodes = document.elementsByTagName( mRoot.elementNames().at(i) );
        for(int j=0; j<nodes.count(); j++)
        {
            positions << XmlDocumentPosition( &mRoot, nodes.at(j).toElement() );
        }
    }
    if( positions.length() == 0 )
    {
        qWarning() << "No root element found. (XmlDocumentModel::getRootPosition)";
        return XmlDocumentPosition(&mRoot, QDomNode().toElement() );
    }
    else if( positions.length() > 1 )
    {
        qWarning() << "Multiple root elements found. Arbitrarily taking the first. (XmlDocumentModel::getRootPosition)";
    }
    return positions.first();
}

QList<XmlDocumentPosition> XmlDocumentModel::getMajorDivisions(QDomDocument document) const
{
    const XmlDocumentPosition rootPosition = getRootPosition(document);
    return getMajorDivisions( rootPosition );
}

QList<XmlDocumentPosition> XmlDocumentModel::getMajorDivisions(XmlDocumentPosition root) const
{
    return mRoot.elementsAtLevel( root.node(), XmlDocumentModel::Major );
}
