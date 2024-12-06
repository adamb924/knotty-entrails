#ifndef DOCUMENTTOKENIZER_H
#define DOCUMENTTOKENIZER_H

#include "knotty-entrails_global.h"

#include <QString>

class QXmlStreamWriter;

#include "datatypes/writingsystem.h"
#include "textitem.h"
#include "xmldocumentmodel.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT DocumentTokenizer
{
public:
    DocumentTokenizer(const XmlDocumentModel & documentModel, const ME::WritingSystem & inputWritingSystem, const ME::WritingSystem & outputWritingSystem, TextItem::Type mode, const QStringList & nonbreakingSequences);

    QString tokenizeFile(const QString & path,  const QString & suffix = QString(".tokenized") ) const;

private:
    void writeTokens(const QString & string, QXmlStreamWriter &out, const QString & glossary = QString() ) const;
    static bool isWhitespace(const QString & string);

    bool elementMatches(const XmlDocumentModelLevel * currentLevel, QXmlStreamReader & in) const;
    void readAndProcessChildren(const XmlDocumentModelLevel * currentLevel, QXmlStreamReader & in, QXmlStreamWriter & out) const;

    static QRegularExpression WHITESPACE_RE;
    static QRegularExpression NONWORD_RE;

    XmlDocumentModel mDocumentModel;
    ME::WritingSystem mInputWritingSystem;
    ME::WritingSystem mOutputWritingSystem;
    TextItem::Type mTextMode;
    QStringList mNonbreakingSequences;
};

} // namespace KE

#endif // DOCUMENTTOKENIZER_H
