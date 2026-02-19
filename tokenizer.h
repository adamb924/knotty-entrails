#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "datatypes/writingsystem.h"
#include "documentmodel.h"
#include "knotty-entrails_global.h"
#include "textitem.h"

namespace KE {

class KNOTTYENTRAILS_EXPORT Tokenizer
{
public:
    Tokenizer(const ME::WritingSystem &inputWritingSystem,
              const ME::WritingSystem &outputWritingSystem,
              KE::TextItem::Type mode,
              KE::DocumentModel model,
              const QStringList &nonbreakingSequences = {});

    void tokenizeFile(const QString &inputPath, const QString &outputPath);

private:
    void writeTokens(const QString &string, QXmlStreamWriter &out);

    static bool isWhitespace(const QString &string);
    bool isNonbreakingSequence(const QString &string);

    ME::WritingSystem mInputWritingSystem;
    ME::WritingSystem mOutputWritingSystem;
    KE::TextItem::Type mTextMode;
    QStringList mNonBreakingSequences;
    KE::DocumentModel mDocumentModel;
};

} // namespace KE

#endif // TOKENIZER_H
