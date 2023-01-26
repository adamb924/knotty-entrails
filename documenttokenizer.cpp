#include "documenttokenizer.h"

#include <QtXml>

#include "textitem.h"

QRegularExpression DocumentTokenizer::WHITESPACE_RE("^\\s+$", QRegularExpression::UseUnicodePropertiesOption);
QRegularExpression DocumentTokenizer::NONWORD_RE("\\b", QRegularExpression::UseUnicodePropertiesOption);

DocumentTokenizer::DocumentTokenizer(const XmlDocumentModel &documentModel, const WritingSystem &inputWritingSystem, const WritingSystem &outputWritingSystem, TextItem::Type mode, const QStringList &nonbreakingSequences)
    : mDocumentModel(documentModel),
      mInputWritingSystem(inputWritingSystem),
      mOutputWritingSystem(outputWritingSystem),
      mTextMode(mode),
      mNonbreakingSequences(nonbreakingSequences)
{

}

QString DocumentTokenizer::tokenizeFile(const QString &path, const QString &suffix) const
{
    QString outPath = path + suffix;
    QFile file(path), outFile(outPath);

    if( file.open( QFile::ReadOnly ) && outFile.open( QFile::WriteOnly ) )
    {
        QXmlStreamReader in(&file);
        QXmlStreamWriter out(&outFile);

        /// position ourselves on the root element, and write it
        in.readNextStartElement();
        out.writeCurrentToken(in);

        /// start as well on the root element
        const XmlDocumentModelLevel * currentLevel = &mDocumentModel.root();

        if( elementMatches(currentLevel,in) )
        {
            readAndProcessChildren(currentLevel,in, out);
        }
        else
        {
            qCritical() << "Root element not found! Expected" << currentLevel->elementNames().join(",") << "but found" << in.name();
            return outPath;
        }
    }
    return outPath;
}

void DocumentTokenizer::writeTokens(const QString &string, QXmlStreamWriter &out, const QString &glossary) const
{
    QStringList tokens = string.split(NONWORD_RE,Qt::SkipEmptyParts);
    for(int i=0; i<tokens.count(); i++)
    {
        QString token = tokens.at(i);

        if( (i+2) < tokens.count() ) /// if there are at least two remaining tokens
        {
            if( mNonbreakingSequences.contains( tokens.at(i+1) ) )
            {
                token = tokens.at(i) + tokens.at(i+1) + tokens.at(i+2);
                i += 2;
            }
        }

        if( isWhitespace(token) )
        {
            out.writeTextElement("whitespace", token );
        }
        else
        {
            if( mTextMode == TextItem::Translated )
            {
                /// also add it to the database
                Form form(mInputWritingSystem, token);

                TextItem item( TextItem::Translated );
                item.input().setForm(form);
                item.input().setGlossaryKey(glossary);
                item.serialize( out );
            }
            else if( mTextMode == TextItem::Simple )
            {
                /// also add it to the database
                Form form(mOutputWritingSystem, token);

                TextItem item( form );
                item.output().setGlossaryKey(glossary);
                item.serialize( out );
            }
        }
    }
}

bool DocumentTokenizer::isWhitespace(const QString &string)
{
    return WHITESPACE_RE.match(string).hasMatch();
}

bool DocumentTokenizer::elementMatches(const XmlDocumentModelLevel *currentLevel, QXmlStreamReader &in) const
{
    return currentLevel->elementNames().contains( in.name() );
}

void DocumentTokenizer::readAndProcessChildren(const XmlDocumentModelLevel *currentLevel, QXmlStreamReader &in, QXmlStreamWriter &out) const
{
    int functionLevelCount = 1;
    while( !in.atEnd() && !( in.isEndElement() && functionLevelCount == 0 && currentLevel->elementNames().contains( in.name() )) )
    {
        in.readNext();

        /// we have encountered a start element
        if( in.isStartElement() )
        {
            functionLevelCount++;

            out.writeCurrentToken( in ); /// write start element
            const XmlDocumentModelLevel * nextLevel = currentLevel->matchingChildElement(in);
            if( nextLevel == nullptr ) /// just go through all of the children
            {
                int level = 0;
                while( !in.atEnd() )
                {
                    in.readNext();
                    if( in.isStartElement() )
                    {
                        functionLevelCount++;
                        level++;
                    }
                    else if ( in.isEndElement() )
                    {
                        functionLevelCount--;
                        if( level == 0 )
                        {

                            out.writeCurrentToken( in );
                            break;
                        }
                        else
                        {
                            level--;
                        }
                    }
                    out.writeCurrentToken( in );
                }
            }
            else /// if(nextLevel != nullptr)
            {
                readAndProcessChildren(nextLevel, in, out);
                functionLevelCount--; /// because we've now passed the closing tag
            }
        }
        else if( currentLevel->containsText() && in.isCharacters() && !in.isWhitespace() )
        {
            QString text = in.text().toString();
            if( text.contains("|") )
            {
                QStringList split = text.split("|");
                writeTokens(split.at(0), out, split.at(1));
            }
            else
            {
                writeTokens(text, out);
            }
        }
        else if( currentLevel->containsText() && in.isWhitespace() )
        {
            out.writeTextElement("whitespace", in.text().toString() );
        }
        else
        {
            if( in.isEndElement() )
            {
                functionLevelCount--;
            }
            out.writeCurrentToken( in );
        }
    }
}
