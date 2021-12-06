#ifndef ABSTRACTPARSEDFORM_H
#define ABSTRACTPARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstracttextitem.h"

class KNOTTYENTRAILS_EXPORT AbstractParsedForm
{
public:
    AbstractParsedForm();
    virtual ~AbstractParsedForm();

    /// Virtual Data Access Methods
    virtual Form form() const = 0;
    virtual void setForm( const Form & form ) = 0;

    virtual AbstractTextItem::WellformednessStatus wellformedness() const = 0;
    virtual void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness) = 0;

    virtual QString glossaryKey() const = 0;
    virtual void setGlossaryKey(const QString &glossaryKey) = 0;

    virtual QString source() const = 0;
    virtual void setSource(const QString & source) = 0;

    virtual Parsing parsing() = 0;
    virtual void setParsing(const Parsing & p, const WritingSystem & summaryWs) = 0;

    virtual QString parsingSummary() const = 0;
    virtual QString parsingIdentifier() const = 0;

protected:
    virtual void setParsingIdentifier(const QString & identifier) = 0;
    virtual void setParsingSummary(const QString & summary) = 0;

public:
    QString summary();

    /// Convenience methods
    void setWellformednessFromMorphology(const Morphology * morphology);
    void setWellformedness(int numberOfParsings);
    bool isWellformed() const;

    /// XML Serialization Methods
    void serialize(const QString & elementName, QXmlStreamWriter & out);
    QDomElement toElement(const QString &elementName, QDomDocument *document);

    /// these functions provide a place to store a list of parsings,
    /// but the data is not guaranteed to persist. in particular it
    /// is not required to be stored (and is not stored in DomTextItem)
    QList<Parsing> inMemoryParsings();
    bool hasInMemoryParsings() const;
    void setInMemoryParsings( const QList<Parsing> & parsings );

protected:
    /// This is a transient data type. DomTextItem will not store it in the DOM
    /// for instance. It makes sense to be able to read it for efficiency purposes,
    /// but it's too time-intensive (for any application really) to serialize and
    /// then deserialize a list of parsings into XML.
    QList<Parsing> mParsings;

};

#endif // ABSTRACTPARSEDFORM_H
