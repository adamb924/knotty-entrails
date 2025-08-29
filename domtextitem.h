#ifndef DOMTEXTITEM_H
#define DOMTEXTITEM_H

#include "knotty-entrails_global.h"

#include "abstracttextitem.h"
#include "domparsedform.h"

#include <QDomElement>

namespace KE {

class AbstractTextAdapter;

class KNOTTYENTRAILS_EXPORT DomTextItem : public AbstractTextItem
{
public:
    DomTextItem(const QDomElement & textItem, const AbstractTextAdapter * adapter);
    ~DomTextItem() override;

    Type type() const override;

    bool modifiable() const override;
    void setModifiable(bool modifiable) override;

    AbstractParsedForm &input() override;
    AbstractParsedForm &output() override;
    const AbstractParsedForm &input() const override;
    const AbstractParsedForm &output() const override;

    /// unline toElement(), this returns the original element rather than constructing a new one
    QDomElement element() const;

    /// XML Names
    static QString XML_TYPE;
    static QString XML_INPUT;
    static QString XML_OUTPUT;
    static QString XML_MODIFIABLE;
    static QString XML_TRUE;
    static QString XML_FALSE;

private:
    void ensureElementExists(QDomElement &element, const QString & elementName);

    QDomElement mTextItemElement;
    ME::Parsing mCachedParsing;
    DomParsedForm * mInput;
    DomParsedForm * mOutput;
};

} // namespace KE

#endif // DOMTEXTITEM_H
