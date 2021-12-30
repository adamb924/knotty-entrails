#ifndef SIMPLETEXTADAPTER_H
#define SIMPLETEXTADAPTER_H

#include "knotty-entrails_global.h"

#include <QString>

#include "abstracttextadapter.h"

class QDomElement;
class QDomDocument;
class DomTextSegment;
class Morphology;

class KNOTTYENTRAILS_EXPORT SimpleTextAdapter : public AbstractTextAdapter
{
public:
    SimpleTextAdapter(const QString & filename, const Morphology * morphology);
    SimpleTextAdapter(QDomElement element, const Morphology * morphology);
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

#endif // SIMPLETEXTADAPTER_H
