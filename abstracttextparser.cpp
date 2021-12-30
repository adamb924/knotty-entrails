#include "abstracttextparser.h"

AbstractTextParser::AbstractTextParser() : mNormalizationFunction( [](Form f) { return f; } )
{
}

AbstractTextParser::AbstractTextParser(std::function<Form (Form)> normalizationFunction) : mNormalizationFunction(normalizationFunction)
{
}

AbstractTextParser::~AbstractTextParser()
{

}
