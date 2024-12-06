#ifndef ABSTRACTPARSEDFORM_H
#define ABSTRACTPARSEDFORM_H

#include "knotty-entrails_global.h"

#include "abstracttextitem.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT AbstractParsedForm
{
public:
    AbstractParsedForm();
    virtual ~AbstractParsedForm();

    /// Virtual Data Access Methods
    virtual ME::Form form() const = 0;
    /// if \a morphology is not equal to nullptr, the parsing and wellformedness are set using \a morphology
    virtual void setForm( const ME::Form & form ) = 0;
    void setForm( const ME::Form & form, const ME::Morphology * morphology );

    virtual AbstractTextItem::WellformednessStatus wellformedness() const = 0;
    virtual void setWellformedness(AbstractTextItem::WellformednessStatus wellformedness) = 0;

    virtual QString glossaryKey() const = 0;
    virtual void setGlossaryKey(const QString &glossaryKey) = 0;

    virtual QString source() const = 0;
    virtual void setSource(const QString & source) = 0;

    virtual ME::Parsing parsing() = 0;
    virtual void setParsing(const ME::Parsing & p) = 0;
    void setParsing(const ME::Morphology * morphology);

    virtual QString parsingIdentifier() const = 0;

protected:
    virtual void setParsingIdentifier(const QString & identifier) = 0;

public:
    QString summary();

    /// Convenience methods
    void setWellformednessFromMorphology(const ME::Morphology * morphology);
    void setWellformedness(int numberOfParsings);
    bool isWellformed() const;

    /// XML Serialization Methods
    void serialize(const QString & elementName, QXmlStreamWriter & out);
    QDomElement toElement(const QString &elementName, QDomDocument *document);

protected:
    /// This is a transient data type. DomTextItem will not store it in the DOM
    /// for instance. It makes sense to be able to read it for efficiency purposes,
    /// but it's too time-intensive (for any application really) to serialize and
    /// then deserialize a list of parsings into XML.
    QList<ME::Parsing> mParsings;

};

} // namespace KE

#endif // ABSTRACTPARSEDFORM_H
