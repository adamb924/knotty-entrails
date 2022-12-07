#ifndef DOCUMENTTOKENIZER_H
#define DOCUMENTTOKENIZER_H

#include "knotty-entrails_global.h"

#include <QString>

class QXmlStreamWriter;
class SoundAndFury;

#include "datatypes/writingsystem.h"
#include "textitem.h"
#include "xmldocumentmodel.h"

class KNOTTYENTRAILS_EXPORT DocumentTokenizer
{
public:
    DocumentTokenizer(const XmlDocumentModel & documentModel, const WritingSystem & inputWritingSystem, const WritingSystem & outputWritingSystem, TextItem::Type mode, const QStringList & nonbreakingSequences);

    QString tokenizeFile(const QString & path,  const QString & suffix = QString(".tokenized") ) const;

private:
    void writeTokens(const QString & string, QXmlStreamWriter &out, const QString & glossary = QString() ) const;
    static bool isWhitespace(const QString & string);

    bool elementMatches(const XmlDocumentModelLevel * currentLevel, QXmlStreamReader & in) const;
    void readAndProcessChildren(const XmlDocumentModelLevel * currentLevel, QXmlStreamReader & in, QXmlStreamWriter & out) const;

    static QRegularExpression WHITESPACE_RE;
    static QRegularExpression NONWORD_RE;

    XmlDocumentModel mDocumentModel;
    WritingSystem mInputWritingSystem;
    WritingSystem mOutputWritingSystem;
    TextItem::Type mTextMode;
    QStringList mNonbreakingSequences;
};

#endif // DOCUMENTTOKENIZER_H
