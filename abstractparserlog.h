#ifndef ABSTRACTPARSERLOG_H
#define ABSTRACTPARSERLOG_H

#include "knotty-entrails_global.h"

#include "datatypes/parsing.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT AbstractParserLog
{
public:
    AbstractParserLog();
    virtual ~AbstractParserLog();

    virtual void addAmbiguousParsing(const QList<ME::Parsing> & parsings) = 0;

    virtual void addFailedParsing(const ME::Form & form) = 0;

    virtual void printReport(const ME::WritingSystem & ws) const = 0;

protected:
    virtual void printList(const QString &label, const QSet<QList<ME::Parsing>> & list, const ME::WritingSystem & ws ) const;
    virtual void printList(const QString &label, const QList<ME::Form> & list) const;

    void printHeader(const QString &label, int number) const;
};

} // namespace KE

#endif // ABSTRACTPARSERLOG_H
