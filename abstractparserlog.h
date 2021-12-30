#ifndef ABSTRACTPARSERLOG_H
#define ABSTRACTPARSERLOG_H

#include "knotty-entrails_global.h"

#include "datatypes/parsing.h"

class KNOTTYENTRAILS_EXPORT AbstractParserLog
{
public:
    AbstractParserLog();
    virtual ~AbstractParserLog();

    virtual void addAmbiguousParsing(const QList<Parsing> & parsings) = 0;

    virtual void printReport(const WritingSystem & ws) const = 0;

protected:
    virtual void printList(const QString &label, const QSet<QList<Parsing>> & list, const WritingSystem & ws ) const;
};

#endif // ABSTRACTPARSERLOG_H
