#ifndef SIMPLEPARSERLOG_H
#define SIMPLEPARSERLOG_H

#include "knotty-entrails_global.h"

#include "abstractparserlog.h"

class KNOTTYENTRAILS_EXPORT SimpleParserLog : public AbstractParserLog
{
public:
    SimpleParserLog();

    void addAmbiguousParsing(const QList<Parsing> & parsings) override;

    void printReport(const WritingSystem & ws) const override;

private:
    QSet<QList<Parsing>> mAmbiguousParsings;
};

#endif // SIMPLEPARSERLOG_H
