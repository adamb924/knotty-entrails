#ifndef ABSTRACTTEXTITEM_H
#define ABSTRACTTEXTITEM_H

#include "knotty-entrails_global.h"
#include "datatypes/parsing.h"
#include "datatypes/generation.h"

class QDomDocument;
class QDomElement;
class AnnotatedTranslation;
class Morphology;
class AbstractParsedForm;

class KNOTTYENTRAILS_EXPORT AbstractTextItem
{
public:
    enum Type { Null, Simple, Translated };
    enum WellformednessStatus { Untested, WellformedSingle, WellformedMultiple, WellformedUnknown, NotWellformed, Ignored };
    enum ParseBy { ParseInputs, ParseOutputs };

    AbstractTextItem();
    virtual ~AbstractTextItem();

    QString summary();

    void serialize(QXmlStreamWriter & out);
    QDomElement toElement(QDomDocument *document);

    virtual Type type() const = 0;

    virtual AbstractParsedForm &input() = 0;
    virtual AbstractParsedForm &output() = 0;
    virtual const AbstractParsedForm &input() const = 0;
    virtual const AbstractParsedForm &output() const = 0;

    /// convenience methods
    void setWellformedness(WellformednessStatus wellformedness, ParseBy parseBy);
    void setParsing(const Parsing & p, const WritingSystem & summaryWs, ParseBy parseBy);

    virtual bool modifiable() const = 0;
    virtual void setModifiable(bool modifiable) = 0;

    QString typeString() const;

    /// static utility functions

    static QString typeToString( Type type );
    static Type typeFromString( const QString & type );

    static QString wellformednessToString( WellformednessStatus wf );
    static WellformednessStatus wellformednessFromString( const QString & type );

    static WellformednessStatus wellformednessStatusFromNumberOfParsings(int numberOfParsings);
    static bool isWellformed(WellformednessStatus status);
};

#endif // ABSTRACTTEXTITEM_H
