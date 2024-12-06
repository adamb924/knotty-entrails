#ifndef SIMPLEPARSERLOG_H
#define SIMPLEPARSERLOG_H

#include "knotty-entrails_global.h"

#include "abstractparserlog.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT SimpleParserLog : public AbstractParserLog
{
public:
    SimpleParserLog();

    void addAmbiguousParsing(const QList<ME::Parsing> & parsings) override;

    void printReport(const ME::WritingSystem & ws) const override;

private:
    QSet<QList<ME::Parsing>> mAmbiguousParsings;
};

} // namespace KE

#endif // SIMPLEPARSERLOG_H
