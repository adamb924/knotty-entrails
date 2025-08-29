#ifndef ABSTRACTTEXTADAPTER_H
#define ABSTRACTTEXTADAPTER_H

#include "knotty-entrails_global.h"

#include <QObject>
#include <QString>
#include <functional>

class QDomDocument;

namespace ME {
class Form;
class Morphology;
class Parsing;
class WritingSystem;
}

namespace KE {

class AbstractTextSegment;
class AbstractTextItem;

class KNOTTYENTRAILS_EXPORT AbstractTextAdapter : public QObject
{
    Q_OBJECT

public:
    AbstractTextAdapter(const ME::Morphology * morphology = nullptr);
    virtual ~AbstractTextAdapter() override;

    ///! \brief Returns the number of translatable lines in a text
    virtual int count() const = 0;

    virtual AbstractTextSegment *segment(int n) = 0;
    virtual const AbstractTextSegment *segment(int n) const = 0;

    /// TODO this probably doesn't need to be a pointer (e.g., QDomNode::ownerDocument() doesn't need to return a pointer)
    QDomDocument *domDocument() const;

    void save(const QString & newFilename ) const;

    void foreachTextItem(std::function<void(AbstractTextItem*)> funct);

    void dumpToDebug() const;

    const ME::Morphology *morphology() const;

public slots:
    void setMorphology(const ME::Morphology * morphology);

signals:
    void formChanged( const ME::Form & oldForm, const ME::Form & newForm );

protected:
    QDomDocument * mDomDocument;
    const ME::Morphology * mMorphology;
};

} // namespace KE

#endif // ABSTRACTTEXTADAPTER_H
