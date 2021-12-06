#include "textitem.h"

#include <QXmlStreamWriter>

TextItem::TextItem(AbstractTextItem::Type type) : mType(type), mModifiable(true)
{

}

TextItem::TextItem(const Form &input, Type type) : mOutput(input), mType(type), mModifiable(true)
{

}

TextItem::~TextItem()
{
}

AbstractParsedForm &TextItem::input()
{
    return mInput;
}

AbstractParsedForm &TextItem::output()
{
    return mOutput;
}

const AbstractParsedForm &TextItem::input() const
{
    return mInput;
}

const AbstractParsedForm &TextItem::output() const
{
    return mOutput;
}

AbstractTextItem::Type TextItem::type() const
{
    return mType;
}

bool TextItem::modifiable() const
{
    return mModifiable;
}

void TextItem::setModifiable(bool modifiable)
{
    mModifiable = modifiable;
}
