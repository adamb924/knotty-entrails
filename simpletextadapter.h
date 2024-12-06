#ifndef SIMPLETEXTADAPTER_H
#define SIMPLETEXTADAPTER_H

#include "knotty-entrails_global.h"

#include <QString>

#include "abstracttextadapter.h"

class QDomElement;
class QDomDocument;

namespace ME {
class Morphology;
}

namespace KE {

class DomTextSegment;

class KNOTTYENTRAILS_EXPORT SimpleTextAdapter : public AbstractTextAdapter
{
public:
    SimpleTextAdapter(const QString & filename, const ME::Morphology * morphology);
    SimpleTextAdapter(QDomElement element, const ME::Morphology * morphology);
    ~SimpleTextAdapter() override;

    int count() const override;

    AbstractTextSegment *segment(int n) override;
    const AbstractTextSegment *segment(int n) const override;

    QString filename() const;

private:
    void loadTextSegmentFromElement(QDomElement element);

    QString mFilename;
    DomTextSegment * mTheTextSegment;
};

} // namespace KE

#endif // SIMPLETEXTADAPTER_H
