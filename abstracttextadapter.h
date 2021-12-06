#ifndef ABSTRACTTEXTADAPTER_H
#define ABSTRACTTEXTADAPTER_H

#include "knotty-entrails_global.h"

class AbstractTextSegment;
class QDomDocument;
class Form;
class Morphology;
class Parsing;
class WritingSystem;
class AbstractTextItem;

#include <QObject>
#include <QString>
#include <functional>

#include "knotty-entrails_global.h"

class KNOTTYENTRAILS_EXPORT AbstractTextAdapter : public QObject
{
    Q_OBJECT

public:
    AbstractTextAdapter(const Morphology * morphology = nullptr);
    virtual ~AbstractTextAdapter();

    ///! \brief Returns the number of translatable lines in a text
    virtual int count() const = 0;

    virtual AbstractTextSegment *segment(int n) = 0;
    virtual const AbstractTextSegment *segment(int n) const = 0;

    QDomDocument *domDocument() const;

    void save(const QString & newFilename ) const;

    void replaceOutput( const Form & replaceThis, const Form & withThis );
    void searchAndReplace( const Form & replaceThis, const Form & withThis );
    void selectOutputParsing(const Form & f, const Parsing & p , const WritingSystem &summaryWs);

    void reparseOutputs(const WritingSystem & summaryWs);
    void setGrammaticalityForOutputs(bool ungrammaticalOnly = false);

    void foreachTextItem(std::function<void(AbstractTextItem*)> funct);

    void dumpToDebug() const;

signals:
    void formChanged( const Form & oldForm, const Form & newForm );

protected:
    QDomDocument * mDomDocument;
    const Morphology * mMorphology;
};

#endif // ABSTRACTTEXTADAPTER_H
