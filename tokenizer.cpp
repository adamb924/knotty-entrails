#include "tokenizer.h"

#include <QFile>
#include <QRegularExpression>
#include <QStack>
#include <QXmlStreamReader>

using namespace KE;

Tokenizer::Tokenizer(const ME::WritingSystem &inputWritingSystem,
                     const ME::WritingSystem &outputWritingSystem,
                     AbstractTextItem::Type mode,
                     DocumentModel model,
                     const QStringList &nonbreakingSequences)
    : mInputWritingSystem(inputWritingSystem)
    , mOutputWritingSystem(outputWritingSystem)
    , mTextMode(mode)
    , mDocumentModel(model)
    , mNonBreakingSequences(nonbreakingSequences)
{}

void Tokenizer::tokenizeFile(const QString &inputPath, const QString &outputPath)
{
    QFile file(inputPath), outFile(outputPath);
    QStack<bool> bParseText;
    bParseText.push(false);

    if (file.open(QFile::ReadOnly) && outFile.open(QFile::WriteOnly)) {
        QXmlStreamReader in(&file);
        QXmlStreamWriter out(&outFile);

        while (!in.atEnd()) {
            in.readNext();

            if (in.isStartElement()) {
                if (mDocumentModel.isInclude(in))
                    bParseText.push(true);
                if (mDocumentModel.isExclude(in))
                    bParseText.push(false);
            } else if (in.isEndElement()) {
                if (mDocumentModel.isInclude(in) || mDocumentModel.isExclude(in))
                    bParseText.pop();
            }

            if (in.isCharacters() && !in.isWhitespace() && bParseText.top()) {
                writeTokens(in.text().toString(), out);
            } else if (in.isWhitespace() && bParseText.top()) {
                out.writeTextElement("whitespace", in.text().toString());
            } else {
                out.writeCurrentToken(in);
            }
        }
    }
}

void Tokenizer::writeTokens(const QString &string, QXmlStreamWriter &out)
{
    static QRegularExpression nonwordRE("\\b", QRegularExpression::UseUnicodePropertiesOption);
    QStringList tokens = string.split(nonwordRE, Qt::SkipEmptyParts);
    for (int i = 0; i < tokens.count(); i++) {
        QString token = tokens.at(i);

        if ((i + 2) < tokens.count()) /// if there are at least two remaining tokens
        {
            if (isNonbreakingSequence(tokens.at(i + 1))) {
                token = tokens.at(i) + tokens.at(i + 1) + tokens.at(i + 2);
                i += 2;
            }
        }

        if (isWhitespace(token)) {
            out.writeTextElement("whitespace", token);
        } else {
            if (mTextMode == KE::TextItem::Translated) {
                ME::Form form(mInputWritingSystem, token);
                KE::TextItem item(KE::TextItem::Translated);
                item.input().setForm(form);
                item.serialize(out);
            } else if (mTextMode == KE::TextItem::Simple) {
                ME::Form form(mOutputWritingSystem, token);
                KE::TextItem item(form);
                item.output().setForm(form);
                item.serialize(out);
            }
        }
    }
}

bool Tokenizer::isWhitespace(const QString &string)
{
    static QRegularExpression re("^\\s+$", QRegularExpression::UseUnicodePropertiesOption);
    return re.match(string).hasMatch();
}

bool Tokenizer::isNonbreakingSequence(const QString &string)
{
    return mNonBreakingSequences.contains(string);
}
